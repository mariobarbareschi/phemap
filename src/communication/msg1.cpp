//===- msg1.cpp ----------------------------------------------------*- C++ -*-===//
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
/// \file msg1.cpp
/// \author Mario Barbareschi
/// \brief This file defines the implementation of the Msg1 class
//===----------------------------------------------------------------------===//

#include "msg1.h"
#include <iomanip>

phemap::Msg1::Msg1 (){
  pufLength = DEFAULT_PUF_LENGTH;
  li = (puf_t*) malloc(pufLength*sizeof(puf_t));
  v1 = (puf_t*) malloc(pufLength*sizeof(puf_t));
  v2 = (puf_t*) malloc(pufLength*sizeof(puf_t));
}

phemap::Msg1::Msg1 (int pufLength){
  this->pufLength = pufLength;
  li = (puf_t*) malloc(pufLength*sizeof(puf_t));
  v1 = (puf_t*) malloc(pufLength*sizeof(puf_t));
  v2 = (puf_t*) malloc(pufLength*sizeof(puf_t));
}

phemap::Msg1::Msg1 (puf_t* buffer, int pufLength){
  this->pufLength = pufLength;
  li = (puf_t*) malloc(pufLength*sizeof(puf_t));
  v1 = (puf_t*) malloc(pufLength*sizeof(puf_t));
  v2 = (puf_t*) malloc(pufLength*sizeof(puf_t));

  memcpy(li, buffer, pufLength);
  memcpy(v1, buffer+pufLength, pufLength);
  memcpy(v2, buffer+2*pufLength,pufLength);
}


phemap::Msg1* phemap::Msg1::setLi(puf_t* li){
  memcpy(this->li, li, pufLength);
  return this;
}

phemap::Msg1* phemap::Msg1::setV1(puf_t* v1){
  memcpy(this->v1, v1, pufLength);
  return this;
}
phemap::Msg1* phemap::Msg1::setV2(puf_t* v2){
  memcpy(this->v2, v2, pufLength);
  return this;
}

int phemap::Msg1::getPufLength() const{
  return pufLength;
}

puf_t* phemap::Msg1::getLi() const{
  return li;
}

puf_t* phemap::Msg1::getV1() const{
  return v1;
}

puf_t* phemap::Msg1::getV2() const{
  return v2;
}

void phemap::Msg1::getLi(puf_t* li) const{
  memcpy(li, this->li, pufLength);
}

void phemap::Msg1::getV1(puf_t* v1) const{
  memcpy(v1, this->v1, pufLength);
}

void phemap::Msg1::getV2(puf_t* v2) const{
  memcpy(v2, this->v2, pufLength);
}

int phemap::Msg1::serialize(puf_t* buffer) const{
  memcpy(buffer, li, pufLength);
  memcpy(buffer+pufLength, v1, pufLength);
  memcpy(buffer+2*pufLength, v2, pufLength);
  return 3*pufLength;
}

bool phemap::Msg1::deserialize(puf_t* buffer, int length){
  if(length != 3*pufLength){
    return false;
  }
  memcpy(li, buffer, pufLength);
  memcpy(v1, buffer+pufLength, pufLength);
  memcpy(v2, buffer+2*pufLength, pufLength);
  return true;
}

std::ostream& phemap::operator<<(std::ostream& os, const phemap::Msg1& msg1){
    os << "Msg1 (";
    os << "0x";
    int i;
    for(i = 0; i < msg1.getPufLength(); i++){
      os << std::hex << std::setw(2) << std::setfill ('0') << static_cast<int>(*(msg1.getLi()+i));
    }
    os << ", 0x";
    for(i = 0; i < msg1.getPufLength(); i++){
      os << std::hex << std::setw(2) << std::setfill ('0') << static_cast<int>(*(msg1.getV1()+i));
    }
    os << ", 0x";
    for(i = 0; i < msg1.getPufLength(); i++){
      os << std::hex << std::setw(2) << std::setfill ('0') << static_cast<int>(*(msg1.getV2()+i));
    }
    os << ");";
    return os;
}

phemap::Msg1::~Msg1 (){
  free(li);
  free(v1);
  free(v2);
}
