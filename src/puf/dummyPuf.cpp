//===- dummyPuf.cpp ----------------------------------------------------*- C++ -*-===//
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
/// \file dummyPuf.cpp
/// \author Mario Barbareschi
/// \brief This file defines the implementation of the DummyPuf class
//===----------------------------------------------------------------------===//

#include <time.h>       /* time */

#include "md5.h"

#include "dummyPuf.h"
extern "C" {
  #include "utils.h"
}

phemap::DummyPuf::DummyPuf(){
    srand(time(NULL));
    this->seed = (puf_t*) malloc(PUF_BYTE_LENGTH*sizeof(puf_t));
    for(int i = 0; i < PUF_BYTE_LENGTH; i++)
        seed[i] = rand();
}

phemap::DummyPuf::DummyPuf(puf_t* seed){
    this->seed = (puf_t*) malloc(PUF_BYTE_LENGTH*sizeof(puf_t));
    this->setSeed(seed);
}

phemap::DummyPuf::~DummyPuf(){
    free(this->seed);
}

void phemap::DummyPuf::generateResponse(const puf_t* challenge, puf_t* response){
    puf_t* trueChallenge = (puf_t*) malloc(PUF_BYTE_LENGTH*sizeof(puf_t));
    xorVector(trueChallenge, seed, challenge, PUF_BYTE_LENGTH);

    memcpy(response, MD5::MD5(trueChallenge, PUF_BYTE_LENGTH).getDigest(), PUF_BYTE_LENGTH);

    free(trueChallenge);
}

int phemap::DummyPuf::getChallengeByteLength(){
    return PUF_BYTE_LENGTH;
}

int phemap::DummyPuf::getResponseByteLength(){
    return PUF_BYTE_LENGTH;
}

void phemap::DummyPuf::setSeed(const puf_t* seed){
    std::memcpy(this->seed, seed, PUF_BYTE_LENGTH);
}

const puf_t* phemap::DummyPuf::getSeed(puf_t* seed){
    std::memcpy(seed, this->seed, PUF_BYTE_LENGTH);
    return this->seed;
}
