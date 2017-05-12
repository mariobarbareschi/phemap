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
/// \brief This file defines the main function for the verifier software
//===----------------------------------------------------------------------===//

#include <iostream>
#include <cstring>
#include "verifier.h"
#include "deviceManager.h"
#include "pufChainFromFile.h"
#include "verifierServer.h"
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

void functionForVerifierThread(phemap::VerifierServer* verifierServer){
  verifierServer->runServerVerifier();
}

int runVerifier(){
  phemap::Verifier* verifier = new phemap::Verifier(16);
  phemap::VerifierServer* verifierServer = new phemap::VerifierServer(verifier);
  std::thread verifierServerThread(functionForVerifierThread,verifierServer);

  std::pair<std::string,phemap::DeviceManager*> pair ("device A",
                                                      (new phemap::DeviceManager())->setDeviceProxy(new phemap::DeviceProxy("device A", new phemap::PufChainFromFile("../resources/deviceLinks.txt"))));
  verifier->getDevicesMap()->insert(pair);
  if(verifier->verifierInitiation("device A")){
    std::cout << "device A initiated and authenticated" << std::endl;
  }else{
    std::cout << "device A not initiated" << std::endl;
  }

  msleep(200);
  while(true){
    std::string dummy;
    std::cin >> dummy;
    if(verifier->verifierAuthentication("device A")) std::cout << "device A authenticated" << std::endl;
  }
  verifierServerThread.join();
  return 0;
}


int main(int argc, char* argv[]){
    return runVerifier();
}
