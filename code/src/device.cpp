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
/// \brief This file defines the main function for the device software
//===----------------------------------------------------------------------===//

#include <iostream>
#include <cstring>
#include "dummyPuf.h"
#include "device.h"
#include "deviceServer.h"
#include <thread>


extern "C"{
#include "utils.h"
}

int msleep(unsigned long milisec)
{
    struct timespec req={0};
    time_t sec=(int)(milisec/1000);
    milisec=milisec-(sec*1000);
    req.tv_sec=sec;
    req.tv_nsec=milisec*1000000L;
    while(nanosleep(&req,&req)==-1)
        continue;
    return 1;
}

void functionForDeviceThread(phemap::DeviceServer* deviceServer){
  deviceServer->runServerDevice();
}

int runDevice(){
  puf_t seed[16] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF, 0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF};
  phemap::Puf* puf = new phemap::DummyPuf(&seed[0]);
  phemap::Device* device = new phemap::Device("device A", puf);
  phemap::DeviceServer* deviceServer = new phemap::DeviceServer(device);

  std::cout << "Running server" << std::endl;
  std::thread deviceServerThread(functionForDeviceThread,deviceServer);

  while(phemap::AUTHENTICATED != device->getState()) continue;

  while(true){
    std::string dummy;
    std::cin >> dummy;
    if(device->authenticateVerifier()) std::cout << "verifier authenticated" << std::endl;
  }

  deviceServerThread.join();
  return 0;
}

int main(int argc, char* argv[]){
    return runDevice();
}
