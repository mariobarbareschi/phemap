//===- verifier.cpp ----------------------------------------------------*- C++ -*-===//
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
/// \file verifier.cpp
/// \author Mario Barbareschi
/// \brief This file defines the implementation of the Verifier class
//===----------------------------------------------------------------------===//

#include "verifier.h"

phemap::Verifier::Verifier (int CRByteLength) : VerifierSkeleton(CRByteLength){
  devicesMap = new DevicesMap_t();
}

DevicesMap_t* phemap::Verifier::getDevicesMap(){
  return devicesMap;
}
bool phemap::Verifier::verifierInitiation(std::string deviceID){
  DevicesMap_t::const_iterator devices = devicesMap->find (deviceID);
  if ( devices == devicesMap->end() ){
    std::cerr << "Device "<< deviceID << " not found" << std::endl;
    return false;
  }

  return devices->second->init();
}

bool phemap::Verifier::verifierAuthentication(std::string deviceID){
  DevicesMap_t::const_iterator devices = devicesMap->find (deviceID);
  if ( devices == devicesMap->end() ){
    std::cerr << "Device "<< deviceID << " not found" << std::endl;
    return false;
  }
  return devices->second->authenticateDevice();
}

bool phemap::Verifier::authentication(const std::string deviceID, const puf_t* li1, puf_t* li2){
  DevicesMap_t::const_iterator devices = devicesMap->find (deviceID);
  if ( devices == devicesMap->end() ){
    std::cerr << "Device "<< deviceID << " not found" << std::endl;
    return false;
  }
  return devices->second->authentication(li1, li2);
}

phemap::Verifier::~Verifier (){
  free(devicesMap);
}
