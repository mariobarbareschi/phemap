//===- device.cpp ----------------------------------------------------*- C++ -*-===//
//
//  Copyright (C) 2017  Mario Barbareschi (mario.barbareschi@unina.it)
//
//  This file is part of PHEMAP.
//
//  PHEMAP is free software: you can redistribute it and/or modify
//  it under the terms of the GNU Affero General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  PHEMAP is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU Affero General Public License for more details.
//
//  You should have received a copy of the GNU Affero General Public License
//  along with PHEMAP. If not, see <https://www.gnu.org/licenses/agpl-3.0.html>.
//
//===----------------------------------------------------------------------===//
/// \file device.cpp
/// \author Mario Barbareschi
/// \brief This file defines the implementation of the Device class
//===----------------------------------------------------------------------===//

extern "C" {
  #include "utils.h"
}

#include <iostream>
#include <assert.h>

#include "device.h"



phemap::Device::Device (std::string deviceID, phemap::Puf* puf) : DeviceSkeleton(deviceID){
  setPuf(puf);
  storage = (puf_t*) malloc(this->puf->getResponseByteLength()*sizeof(puf_t));
  verifierProxy = new phemap::VerifierProxy(this->puf->getResponseByteLength());
}

phemap::Device::Device (std::string deviceID, phemap::Puf* puf, int sentinel) : DeviceSkeleton(deviceID, sentinel){
  setPuf(puf);
  storage = (puf_t*) malloc(this->puf->getResponseByteLength()*sizeof(puf_t));
  verifierProxy = new phemap::VerifierProxy(this->puf->getResponseByteLength());
}

phemap::Puf* phemap::Device::getPuf(){
  return puf;
}

phemap::Device* phemap::Device::setPuf(phemap::Puf* puf){
  /*Challenge and response must have the same length*/
  assert(puf->getChallengeByteLength() == puf->getResponseByteLength());
  this->puf = puf;
  return this;
}

bool phemap::Device::verifyCRP(const puf_t* challenge, const puf_t* response){
  if(this->puf != NULL){
    puf_t* pufResponse = (puf_t*) malloc(puf->getResponseByteLength()*sizeof(puf_t));
    this->puf->generateResponse(challenge, pufResponse);
    bool test = (0 == memcmp(pufResponse, response, puf->getResponseByteLength()) );
    free(pufResponse);
    return test;
  }else{
    std::cerr << "The device has no a valid puf" << std::endl;
    return false;
  }
}

bool phemap::Device::verifyCRPWithSentinel(const puf_t* challenge, const puf_t* response){
  if(this->puf != NULL){
    puf_t* pufResponse = (puf_t*) malloc(puf->getResponseByteLength()*sizeof(puf_t));
    memcpy(pufResponse, challenge, puf->getResponseByteLength());
    if(false == countLink(false)){
      this->puf->generateResponse(pufResponse, pufResponse);
    }
    this->puf->generateResponse(pufResponse, pufResponse);
    bool test = (0 == memcmp(pufResponse, response, puf->getResponseByteLength()) );
    free(pufResponse);
    return test;
  }else{
    std::cerr << "The device has no a valid puf" << std::endl;
    return false;
  }
}


void phemap::Device::getNextPufLink(puf_t* link, bool ignoreSentinel){
  if(false == ignoreSentinel && false == countLink(true)){
    this->puf->generateResponse(storage, storage);
  }
  this->puf->generateResponse(storage, storage);
  if(link != 0) memcpy(link, storage, puf->getResponseByteLength());
}

bool phemap::Device::verifierInitiation(const phemap::Msg1* msg1, phemap::Msg2* msg2){
  bool outcome = false;

  puf_t* xorAcc = (puf_t*) malloc(puf->getResponseByteLength()*sizeof(puf_t));
  xorVector(xorAcc, msg1->getV1(), msg1->getV2(), puf->getResponseByteLength());

  puf_t* pufChain = (puf_t*) malloc(puf->getResponseByteLength()*sizeof(puf_t));
  memcpy(pufChain, msg1->getLi(), puf->getResponseByteLength());

  /*Instead of verifying the accumulation of xor, we can elide each link from the v1 xor v2*/
  for(int i = 0; i < this->sentinel - 2; i++){
    this->puf->generateResponse(pufChain, pufChain);
    xorVector(xorAcc, xorAcc, pufChain, puf->getResponseByteLength());
  }
  /*At this point, xorAcc should contain the link l[i+S-1], that can be easily verified*/
  if(!verifyCRP(pufChain, xorAcc)){
    std::cerr << "Error: msg1 check failed" << std::endl;
  }else{
    outcome = true;
    flushStorage();
    /*We need to go further!*/
    this->puf->generateResponse(pufChain, pufChain);

    puf_t* nonce = (puf_t*) malloc(puf->getResponseByteLength()*sizeof(puf_t));
    puf_t* d1 = (puf_t*) malloc(puf->getResponseByteLength()*sizeof(puf_t));
    puf_t* d2 = (puf_t*) malloc(puf->getResponseByteLength()*sizeof(puf_t));

    getRandomNonce(nonce, puf->getResponseByteLength());

    this->puf->generateResponse(pufChain, pufChain);
    xorVector(d1, pufChain, nonce, puf->getResponseByteLength());

    this->puf->generateResponse(pufChain, pufChain);
    xorVector(d2, pufChain, nonce, puf->getResponseByteLength());

    setStorage(d2);

    setState(INITIATED);

    msg2->setD1(d1);
    msg2->setD2(d2);
    free(d1);
    free(d2);
    free(nonce);
  }

  free(xorAcc);
  free(pufChain);
  return outcome;
}

bool phemap::Device::verifierCompletion(const phemap::Msg3* msg3){
  bool outcome = false;
  puf_t* pufChain = (puf_t*) malloc(puf->getResponseByteLength()*sizeof(puf_t));
  puf_t* xorAcc = (puf_t*) malloc(puf->getResponseByteLength()*sizeof(puf_t));
  puf_t* v3XorD2 = (puf_t*) malloc(puf->getResponseByteLength()*sizeof(puf_t));
  memcpy(pufChain, msg3->getLi(), puf->getResponseByteLength());

  for(int i = 0; i < this->sentinel+1; i++){
    this->puf->generateResponse(pufChain, pufChain);
  }
  /*At this point, pufchain should contain L(i+s+1) link*/
  memcpy(xorAcc, pufChain, puf->getResponseByteLength());
  this->puf->generateResponse(pufChain, pufChain);
  xorVector(xorAcc, xorAcc, pufChain, puf->getResponseByteLength());
  xorVector(v3XorD2, this->storage, msg3->getV3(), puf->getResponseByteLength());

  if(0 != memcmp(v3XorD2, xorAcc, puf->getResponseByteLength())){
    std::cerr << "Error: msg3 check failed" << std::endl;
  }else{
    outcome = true;
    flushStorage();
    this->puf->generateResponse(pufChain, pufChain);
    setStorage(pufChain);
    setState(AUTHENTICATED);
    /*Set sentinel from now*/
    resetlinkCounter();
    std::cout << "Initiation by the verifier completed!" << std::endl;
  }

  free(pufChain);
  free(v3XorD2);
  free(xorAcc);
  return outcome;
}

void phemap::Device::flushStorage(){
  memset(storage, 0x00 , puf->getResponseByteLength());
}

phemap::Device* phemap::Device::setStorage(puf_t* value){
  memcpy(storage, value, puf->getResponseByteLength());
  std::cout << "Storage updated: ";
  printHexBuffer(storage, puf->getResponseByteLength());
  std::cout << std::endl;
  return this;
}

phemap::Device::~Device (){
  free(storage);
  free(verifierProxy);
}

bool phemap::Device::authentication(const puf_t* li1, puf_t* li2){
  if(verifyCRPWithSentinel(storage, li1)){
    getNextPufLink(0, false);
    getNextPufLink(li2, false);
    return true;
  }else{
    return false;
  }
}

bool phemap::Device::authenticateVerifier(){
  bool outcome = false;
  if(INITIATED == getState() || AUTHENTICATED == getState()){
    puf_t* li2 = (puf_t*) malloc(puf->getResponseByteLength()*sizeof(puf_t));
    getNextPufLink(0, false);
    verifierProxy->authentication(getDeviceID(), storage, li2);
    getNextPufLink(0, false);
    if(0 == memcmp(li2, storage, puf->getResponseByteLength() ) ){
      outcome = true;

    } else {
      outcome = false;
    }
    free(li2);
  } else {
    std:std::cerr << "Device not initiated, cannot authenticate the verifier " << std::endl;
    outcome = false;
  }
  return outcome;
}
