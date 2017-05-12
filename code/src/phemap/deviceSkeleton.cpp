//===- deviceSkeleton.cpp ----------------------------------------------------*- C++ -*-===//
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
/// \file deviceSkeleton.cpp
/// \author Mario Barbareschi
/// \brief This file defines the implementation of the asbtract class
/// DeviceSkeleton
//===----------------------------------------------------------------------===//

#include "deviceSkeleton.h"
#include <assert.h>

phemap::DeviceSkeleton::DeviceSkeleton () : deviceID(""), linkCounter(0) {
    state = DISCONNECTED;
    setSentinel(DEFAULT_SENTINEL);
}

phemap::DeviceSkeleton::DeviceSkeleton (std::string deviceID) : deviceID(deviceID), linkCounter(0) {
  state = DISCONNECTED;
  setSentinel(DEFAULT_SENTINEL);
}

phemap::DeviceSkeleton::DeviceSkeleton (std::string deviceID, int sentinel) : deviceID(deviceID), linkCounter(0){
  state = DISCONNECTED;
  setSentinel(sentinel);
}

phemap::DeviceSkeleton* phemap::DeviceSkeleton::setDeviceID(std::string){
  this->deviceID = deviceID;
  return this;
}

std::string phemap::DeviceSkeleton::getDeviceID(){
  return deviceID;
}

int phemap::DeviceSkeleton::getSentinel(){
  return sentinel;
}

/*Returns true if the link is not a sentinel*/
bool phemap::DeviceSkeleton::countLink(bool permanent){
  if(permanent)
    return 0 != (++linkCounter)%sentinel;
  else
    return 0 != (linkCounter+1)%sentinel;
}

void phemap::DeviceSkeleton::resetlinkCounter(){
  linkCounter = 0;
}

phemap::DeviceState phemap::DeviceSkeleton::getState(){
  return state;
}

phemap::DeviceSkeleton* phemap::DeviceSkeleton::setState(phemap::DeviceState state){
  this->state = state;
  return this;
}

phemap::DeviceSkeleton* phemap::DeviceSkeleton::setSentinel(int sentinel){
  /*Sentinel must be greater than 3*/
  assert(sentinel > 3);
  this->sentinel = sentinel;
  return this;
}
