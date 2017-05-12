//===- msg2.cpp ----------------------------------------------------*- C++ -*-===//
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
/// \file msg2.cpp
/// \author Mario Barbareschi
/// \brief This file defines the implementation of the Msg2 class
//===----------------------------------------------------------------------===//


#include "msg2.h"
#include <iomanip>

phemap::Msg2::Msg2 (){
  pufLength = DEFAULT_PUF_LENGTH;
  d1 = (puf_t*) malloc(pufLength*sizeof(puf_t));
  d2 = (puf_t*) malloc(pufLength*sizeof(puf_t));
}

phemap::Msg2::Msg2 (int pufLength){
  this->pufLength = pufLength;
  d1 = (puf_t*) malloc(pufLength*sizeof(puf_t));
  d2 = (puf_t*) malloc(pufLength*sizeof(puf_t));
}

phemap::Msg2::Msg2 (puf_t* buffer, int pufLength){
  this->pufLength = pufLength;
  d1 = (puf_t*) malloc(pufLength*sizeof(puf_t));
  d2 = (puf_t*) malloc(pufLength*sizeof(puf_t));

  memcpy(d1, buffer, pufLength);
  memcpy(d2, buffer+pufLength, pufLength);
}


phemap::Msg2* phemap::Msg2::setD1(puf_t* d1){
  memcpy(this->d1, d1, pufLength);
  return this;
}

phemap::Msg2* phemap::Msg2::setD2(puf_t* d2){
  memcpy(this->d2, d2, pufLength);
  return this;
}

int phemap::Msg2::getPufLength() const{
  return pufLength;
}

int phemap::Msg2::serialize(puf_t* buffer) const{
  memcpy(buffer, d1, pufLength);
  memcpy(buffer+pufLength, d2, pufLength);
  return 2*pufLength;
}

bool phemap::Msg2::deserialize(puf_t* buffer, int length){
  if(length != 2*pufLength){
    return false;
  }
  memcpy(d1, buffer, pufLength);
  memcpy(d2, buffer+pufLength, pufLength);
  return true;
}

puf_t* phemap::Msg2::getD1() const{
  return d1;
}

puf_t* phemap::Msg2::getD2(void) const{
  return d2;
}

void phemap::Msg2::getD1(puf_t* d1) const{
  memcpy(d1, this->d1, pufLength);
}

void phemap::Msg2::getD2(puf_t* d2) const{
  memcpy(d2, this->d2, pufLength);
}

std::ostream& phemap::operator<<(std::ostream& os, const phemap::Msg2& msg2){
    os << "Msg2 (";
    os << "0x";
    int i;
    for(i = 0; i < msg2.getPufLength(); i++){
      os << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(*(msg2.getD1()+i));
    }
    os << ", 0x";
    for(i = 0; i < msg2.getPufLength(); i++){
      os << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(*(msg2.getD2()+i));
    }
    os << ");";
    return os;
}

phemap::Msg2::~Msg2 (){
  free(d1);
  free(d2);
}
