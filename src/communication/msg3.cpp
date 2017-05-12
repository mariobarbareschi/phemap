//===- msg3.cpp ----------------------------------------------------*- C++ -*-===//
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
/// \file msg3.cpp
/// \author Mario Barbareschi
/// \brief This file defines the implementation of the Msg3 class
//===----------------------------------------------------------------------===//


#include "msg3.h"
#include <iomanip>

phemap::Msg3::Msg3 (){
  pufLength = DEFAULT_PUF_LENGTH;
  li = (puf_t*) malloc(pufLength*sizeof(puf_t));
  v3 = (puf_t*) malloc(pufLength*sizeof(puf_t));
}

phemap::Msg3::Msg3 (int pufLength){
  this->pufLength = pufLength;
  li = (puf_t*) malloc(pufLength*sizeof(puf_t));
  v3 = (puf_t*) malloc(pufLength*sizeof(puf_t));
}

phemap::Msg3::Msg3 (puf_t* buffer, int pufLength){
  this->pufLength = pufLength;
  li = (puf_t*) malloc(pufLength*sizeof(puf_t));
  v3 = (puf_t*) malloc(pufLength*sizeof(puf_t));

  memcpy(li, buffer, pufLength);
  memcpy(v3, buffer+pufLength, pufLength);
}


phemap::Msg3* phemap::Msg3::setLi(puf_t* li){
  memcpy(this->li, li, pufLength);
  return this;
}

phemap::Msg3* phemap::Msg3::setV3(puf_t* v3){
  memcpy(this->v3, v3, pufLength);
  return this;
}

int phemap::Msg3::getPufLength() const{
  return pufLength;
}

int phemap::Msg3::serialize(puf_t* buffer) const{
  memcpy(buffer, li, pufLength);
  memcpy(buffer+pufLength, v3, pufLength);
  return 2*pufLength;
}

bool phemap::Msg3::deserialize(puf_t* buffer, int length){
  if(length != 2*pufLength){
    return false;
  }
  memcpy(li, buffer, pufLength);
  memcpy(v3, buffer+pufLength, pufLength);
  return true;
}


puf_t* phemap::Msg3::getLi() const{
  return li;
}

puf_t* phemap::Msg3::getV3(void) const{
  return v3;
}

void phemap::Msg3::getLi(puf_t* li) const{
  memcpy(li, this->li, pufLength);
}

void phemap::Msg3::getV3(puf_t* v3) const{
  memcpy(v3, this->v3, pufLength);
}

std::ostream& phemap::operator<<(std::ostream& os, const phemap::Msg3& Msg3){
    os << "Msg3 (";
    os << "0x";
    int i;
    for(i = 0; i < Msg3.getPufLength(); i++){
      os << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(*(Msg3.getLi()+i));
    }
    os << ", 0x";
    for(i = 0; i < Msg3.getPufLength(); i++){
      os << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(*(Msg3.getV3()+i));
    }
    os << ");";
    return os;
}

phemap::Msg3::~Msg3 (){
  free(li);
  free(v3);
}
