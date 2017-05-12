//===- deviceProxy.cpp ----------------------------------------------------*- C++ -*-===//
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
/// \file deviceProxy.cpp
/// \author Mario Barbareschi
/// \brief This file defines the implementation of the DeviceProxy class
//===----------------------------------------------------------------------===//

extern "C" {
  #include "utils.h"
}

#include <iostream>
#include <iomanip>
#include <assert.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#include "deviceProxy.h"



phemap::DeviceProxy::DeviceProxy (std::string deviceID, phemap::PufChain* pufChain) : DeviceSkeleton(deviceID), pufChain(pufChain){
  setSentinel(DEFAULT_SENTINEL);
}

phemap::DeviceProxy::DeviceProxy (std::string deviceID, phemap::PufChain* pufChain, int sentinel) : DeviceSkeleton(deviceID), pufChain(pufChain){
  setSentinel(sentinel);
}

phemap::PufChain* phemap::DeviceProxy::getPufChain(){
  return pufChain;
}

void phemap::DeviceProxy::getNextPufLink(puf_t* link, bool ignoreSentinel){
  if(false == ignoreSentinel && true == countLink(true)){
    puf_t* tmp = (puf_t*) malloc(this->pufChain->getCRByteLength()*sizeof(puf_t));
    this->pufChain->getNextLink(tmp);
    free(tmp);
  }
  this->pufChain->getNextLink(link);
  countLink(true);
}

void phemap::DeviceProxy::setPufChain(phemap::PufChain* pufChain){
  this->pufChain = pufChain;
}

bool phemap::DeviceProxy::verifierInitiation(const phemap::Msg1* msg1, phemap::Msg2* msg2){
  int sockfd, portno, n;
   struct sockaddr_in serv_addr;
   struct hostent *server;

   portno = DEVICE_PORT_NUMBER;
   sockfd = socket(AF_INET, SOCK_STREAM, 0);
   if (sockfd < 0)
       perror("ERROR opening socket");
   server = gethostbyname("localhost");
   if (server == NULL) {
       fprintf(stderr,"ERROR, no such host\n");
       exit(0);
   }
   bzero((char *) &serv_addr, sizeof(serv_addr));
   serv_addr.sin_family = AF_INET;
   bcopy((char *)server->h_addr,
        (char *)&serv_addr.sin_addr.s_addr,
        server->h_length);
   serv_addr.sin_port = htons(portno);
   if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
       perror("ERROR connecting");

   uint8_t* buffer = (uint8_t*) malloc(pufChain->getCRByteLength()*3);

   msg1->serialize(buffer);

   n = write(sockfd, buffer, pufChain->getCRByteLength()*3);
   std::cout << "verifierInitiation: I'm sending " << (*msg1);
   std::cout << std::endl;

   if (n < 0)
        perror("ERROR writing to socket");
   bzero(buffer,pufChain->getCRByteLength()*2);
   n = read(sockfd, buffer, pufChain->getCRByteLength()*2);
   if (n < 0)
        perror("ERROR reading from socket");

    msg2->deserialize(buffer, n);;
    free(buffer);

   close(sockfd);
     return true;
}

bool phemap::DeviceProxy::verifierCompletion(const phemap::Msg3* msg3){
  int sockfd, portno, n;
   struct sockaddr_in serv_addr;
   struct hostent *server;

   portno = DEVICE_PORT_NUMBER;
   sockfd = socket(AF_INET, SOCK_STREAM, 0);
   if (sockfd < 0)
       perror("ERROR opening socket");
   server = gethostbyname("localhost");
   if (server == NULL) {
       fprintf(stderr,"ERROR, no such host\n");
       exit(0);
   }
   bzero((char *) &serv_addr, sizeof(serv_addr));
   serv_addr.sin_family = AF_INET;
   bcopy((char *)server->h_addr,
        (char *)&serv_addr.sin_addr.s_addr,
        server->h_length);
   serv_addr.sin_port = htons(portno);
   if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
       perror("ERROR connecting");

   uint8_t* buffer = (uint8_t*) malloc(pufChain->getCRByteLength()*2);

   msg3->serialize(buffer);

   n = write(sockfd, buffer, pufChain->getCRByteLength()*2);
   std::cout << "verifierCompletion: I'm sending " << (*msg3);
   std::cout << std::endl;

   if (n < 0)
        perror("ERROR writing to socket");
    free(buffer);

   close(sockfd);

     return true;
}

bool phemap::DeviceProxy::authentication(const puf_t* li1, puf_t* li2){
  int sockfd, portno, n;
   struct sockaddr_in serv_addr;
   struct hostent *server;

   portno = DEVICE_PORT_NUMBER;
   sockfd = socket(AF_INET, SOCK_STREAM, 0);
   if (sockfd < 0)
       perror("ERROR opening socket");
   server = gethostbyname("localhost");
   if (server == NULL) {
       fprintf(stderr,"ERROR, no such host\n");
       exit(0);
   }
   bzero((char *) &serv_addr, sizeof(serv_addr));
   serv_addr.sin_family = AF_INET;
   bcopy((char *)server->h_addr,
        (char *)&serv_addr.sin_addr.s_addr,
        server->h_length);
   serv_addr.sin_port = htons(portno);
   if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
       perror("ERROR connecting");

   n = write(sockfd, li1, pufChain->getCRByteLength());
   std::cout << "authentication: I'm sending ";
   printHexBuffer(li1, pufChain->getCRByteLength());
   std::cout << std::endl;

   if (n < 0)
        perror("ERROR writing to socket");

  n = read(sockfd, li2, pufChain->getCRByteLength());
  if (n < 0)
       perror("ERROR reading from socket");

   std::cout << "authentication: I'm receiving ";
   printHexBuffer(li2, pufChain->getCRByteLength());
   std::cout << std::endl;
   close(sockfd);
  return true;

}
