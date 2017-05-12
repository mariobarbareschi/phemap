//===- verifierProxy.cpp ----------------------------------------------------*- C++ -*-===//
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
/// \file verifierProxy.cpp
/// \author Mario Barbareschi
/// \brief This file defines the implementation of the VerifierProxy class
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

#include "verifierProxy.h"

phemap::VerifierProxy::VerifierProxy(int CRByteLength ) : VerifierSkeleton(CRByteLength){

}

bool phemap::VerifierProxy::authentication(const std::string deviceID, const puf_t* li1, puf_t* li2){
  int sockfd, portno, n;
   struct sockaddr_in serv_addr;
   struct hostent *server;

   portno = VERIFIER_PORT_NUMBER;
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

  int messageSize = deviceID.size()+getCRByteLength();
   uint8_t* buffer = (uint8_t*) malloc(messageSize);

   memcpy(buffer, li1, getCRByteLength());
   memcpy(buffer+getCRByteLength(), deviceID.c_str(), deviceID.size());

   n = write(sockfd, buffer, messageSize);
   std::cout << "authentication: I'm sending " << deviceID << "; ";
   printHexBuffer(li1, getCRByteLength());
   std::cout << std::endl;

   if (n < 0)
        perror("ERROR writing to socket");
   n = read(sockfd, li2, getCRByteLength());

   std::cout << "authentication: I'm receiving ";
   printHexBuffer(li2, getCRByteLength());
   std::cout << std::endl;

   if (n < 0)
        perror("ERROR reading from socket");

    free(buffer);

   close(sockfd);
     return true;
}
