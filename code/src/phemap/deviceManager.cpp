//===- deviceManager.cpp ----------------------------------------------------*- C++ -*-===//
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
/// \file deviceManager.cpp
/// \author Mario Barbareschi
/// \brief This file defines the implementation of the DeviceManager class
//===----------------------------------------------------------------------===//

extern "C" {
  #include "utils.h"
}

#include "deviceManager.h"

phemap::DeviceManager::DeviceManager(phemap::DeviceProxy* device) : device(device){

}

phemap::DeviceManager* phemap::DeviceManager::setDeviceProxy(phemap::DeviceProxy* device){
  this->device = device;
  return this;
}


bool phemap::DeviceManager::init(){
  bool outcome = true;
  puf_t* root = (puf_t*) malloc(device->getPufChain()->getCRByteLength()*sizeof(puf_t));
  puf_t* v1 = (puf_t*) malloc(device->getPufChain()->getCRByteLength()*sizeof(puf_t));
  puf_t* v2 = (puf_t*) malloc(device->getPufChain()->getCRByteLength()*sizeof(puf_t));
  puf_t* nonce = (puf_t*) malloc(device->getPufChain()->getCRByteLength()*sizeof(puf_t));
  puf_t* pufChain = (puf_t*) malloc(device->getPufChain()->getCRByteLength()*sizeof(puf_t));

  device->getPufChain()->getNextLink(root);

  getRandomNonce(nonce, device->getPufChain()->getCRByteLength());

  device->getPufChain()->getNextLink(v1);
  for(int i = 0; i < device->getSentinel() - 4; i++){
    device->getPufChain()->getNextLink(pufChain);
    xorVector(v1, v1, pufChain, device->getPufChain()->getCRByteLength());
  }
  xorVector(v1, v1, nonce, device->getPufChain()->getCRByteLength());

  device->getPufChain()->getNextLink(v2);
  device->getPufChain()->getNextLink(pufChain);
  xorVector(v2, xorVector(v2, v2, nonce, device->getPufChain()->getCRByteLength()),
  pufChain,
  device->getPufChain()->getCRByteLength());

  Msg1 * msg1 = new Msg1(device->getPufChain()->getCRByteLength());
  msg1->setLi(root)->setV1(v1)->setV2(v2);
  Msg2* msg2 = new Msg2(device->getPufChain()->getCRByteLength());

  //actually the proxy is called
  outcome &= device->verifierInitiation(msg1, msg2);

  /*Set memory free of useless information*/
  free(nonce);
  free(v2);
  free(v1);
  free(msg1);

  if(!outcome){
    device->setState(UNKNOWN);
  } else {
    device->setState(INITIATED);

    puf_t* lis = (puf_t*) malloc(device->getPufChain()->getCRByteLength()*sizeof(puf_t));
    puf_t* lis1 = (puf_t*) malloc(device->getPufChain()->getCRByteLength()*sizeof(puf_t));
    puf_t* d1xord2 = (puf_t*) malloc(device->getPufChain()->getCRByteLength()*sizeof(puf_t));

    device->getPufChain()->getNextLink(lis);
    device->getPufChain()->getNextLink(lis1);
    xorVector(pufChain, lis, lis1, device->getPufChain()->getCRByteLength());
    xorVector(d1xord2, msg2->getD1(), msg2->getD2(), device->getPufChain()->getCRByteLength());

    if(0 == memcmp(d1xord2, pufChain, device->getPufChain()->getCRByteLength())){
      /*Set memory free of useless information. We do not delete lis because we need it to extract device's nonce*/
      free(lis1);
      free(d1xord2);

      Msg3* msg3 = new Msg3(device->getPufChain()->getCRByteLength());
      puf_t* v3 = (puf_t*) malloc(device->getPufChain()->getCRByteLength()*sizeof(puf_t));
      xorVector(v3, msg2->getD1(), lis, device->getPufChain()->getCRByteLength());
      device->getPufChain()->getNextLink(pufChain);
      xorVector(v3, v3, pufChain, device->getPufChain()->getCRByteLength());
      msg3->setLi(root)->setV3(v3);

      //actually, the proxy is called
      outcome &= device->verifierCompletion(msg3);

      /*Set memory free of useless information*/
      free(lis);
      free(msg2);
      free(msg3);
      free(v3);

      if(!outcome){
        device->setState(UNKNOWN);
      } else {
        device->setState(AUTHENTICATED);

        /*Jump to the next link, such that it is the first link for auth*/
        device->getPufChain()->getNextLink(pufChain);
        device->resetlinkCounter();
      } //Outcome of second communication
    }else{
      device->setState(ERROR);
      outcome = false;
    }
  } //Outcome of first communication



  free(pufChain);
  free(root);
  return outcome;
}

bool phemap::DeviceManager::authenticateDevice(){
  puf_t* li1 = (puf_t*) malloc(device->getPufChain()->getCRByteLength()*sizeof(puf_t));
  puf_t* li2Received = (puf_t*) malloc(device->getPufChain()->getCRByteLength()*sizeof(puf_t));
  puf_t* li2 = (puf_t*) malloc(device->getPufChain()->getCRByteLength()*sizeof(puf_t));
  getNextPufLink(li1, false);

  //the autentication function is here intended to be resolved by the proxy, which communicates with the real device
  bool outcome = device->authentication(li1, li2Received);
  if(!outcome){
    device->setState(UNKNOWN);
  } else{
    getNextPufLink(li2, false);
    if(0 == memcmp(li2, li2Received, device->getPufChain()->getCRByteLength())){
      device->setState(AUTHENTICATED);
    } else {
      device->setState(ERROR);
      outcome = false;
    }
  }
  free(li1);
  free(li2);
  free(li2Received);
  return outcome;
}

bool phemap::DeviceManager::authentication(const puf_t* li1Received, puf_t* li2){
  bool outcome = false;
  puf_t* li1 = (puf_t*) malloc(device->getPufChain()->getCRByteLength()*sizeof(puf_t));
  peekNextPufLink(li1, false);
  if(0 == memcmp(li1, li1Received, device->getPufChain()->getCRByteLength())){
    outcome = true;
    getNextPufLink(0, false);
    getNextPufLink(li2, false);
  } else {
    outcome = false;
  }
  free(li1);
  return outcome;
}

void phemap::DeviceManager::getNextPufLink(puf_t* link, bool ignoreSentinel){
  puf_t* chain = (puf_t*) malloc(device->getPufChain()->getCRByteLength()*sizeof(puf_t));
  if(false == ignoreSentinel && false == device->countLink(true)){
    device->getPufChain()->getNextLink(chain);
  }
  device->getPufChain()->getNextLink(chain);
  if(link != 0) memcpy(link, chain, device->getPufChain()->getCRByteLength());
  free(chain);
}

void phemap::DeviceManager::peekNextPufLink(puf_t* link, bool ignoreSentinel){
  if(false == ignoreSentinel && false == device->countLink(false)){
    device->getPufChain()->peekLink(link, 2);
  } else{
    device->getPufChain()->peekLink(link,1);
  }
}
