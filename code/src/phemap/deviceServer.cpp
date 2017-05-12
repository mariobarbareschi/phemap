//===- deviceServer.cpp ----------------------------------------------------*- C++ -*-===//
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
/// \file deviceServer.cpp
/// \author Mario Barbareschi
/// \brief This file defines the implementation of the DeviceServer class
//===----------------------------------------------------------------------===//

extern "C" {
  #include "utils.h"
}

#include "deviceServer.h"

#include <iostream>
#include <iomanip>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


phemap::DeviceServer::DeviceServer (phemap::Device* device) : device(device){

}

phemap::DeviceServer* phemap::DeviceServer::setDevice(Device* device){
  this->device = device;
  return this;
}

void phemap::DeviceServer::runServerDevice(){
  int sockfd, newsockfd, portno;
  socklen_t clilen;
  struct sockaddr_in serv_addr, cli_addr;
  int n;

  // clear address structure
  bzero((char *) &serv_addr, sizeof(serv_addr));

  portno = DEVICE_PORT_NUMBER;

  /* setup the host_addr structure for use in bind call */
  // server byte order
  serv_addr.sin_family = AF_INET;

  // automatically be filled with current host's IP address
  serv_addr.sin_addr.s_addr = INADDR_ANY;

  // convert short integer value for port must be converted into network byte order
  serv_addr.sin_port = htons(portno);


  while(true){
    // create a socket
    // socket(int domain, int type, int protocol)
    sockfd =  socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    perror("ERROR opening socket");

    int t = 1;
    if (setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&t,sizeof(int)) == -1)
    {
        perror("Setsockopt");
        exit(1);
    }

    // bind(int fd, struct sockaddr *local_addr, socklen_t addr_length)
    // bind() passes file descriptor, the address structure,
    // and the length of the address structure
    // This bind() call will bind  the socket to the current IP address on port, portno
    if (bind(sockfd, (struct sockaddr *) &serv_addr,
    sizeof(serv_addr)) < 0)
    perror("ERROR on binding");

    // This listen() call tells the socket to listen to the incoming connections.
    // The listen() function places all incoming connection into a backlog queue
    // until accept() call accepts the connection.
    // Here, we set the maximum size for the backlog queue to 5.
    listen(sockfd,5);

    // The accept() call actually accepts an incoming connection
    clilen = sizeof(cli_addr);

    // This accept() function will write the connecting client's address info
    // into the the address structure and the size of that structure is clilen.
    // The accept() returns a new socket file descriptor for the accepted connection.
    // So, the original socket file descriptor can continue to be used
    // for accepting new connections while the new socker file descriptor is used for
    // communicating with the connected client.
    newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
      if (newsockfd < 0) perror("ERROR on accept");

      printf("server: got connection from %s port %d\n",
      inet_ntoa(cli_addr.sin_addr), ntohs(cli_addr.sin_port));


      // This send() function sends the 13 bytes of the string to the new socket

      uint8_t* buffer = (uint8_t*) malloc(device->getPuf()->getResponseByteLength()*3);

      n = read(newsockfd,buffer,device->getPuf()->getResponseByteLength()*3);

      if (n < 0) perror("ERROR reading from socket");

      if(n == device->getPuf()->getResponseByteLength()*3){

        Msg1* msg1 = new Msg1(buffer, device->getPuf()->getResponseByteLength());

        std::cout << "runServerDevice: I'm receiving " << *msg1 << std::endl;

        Msg2* msg2 = new Msg2(device->getPuf()->getResponseByteLength());

        device->verifierInitiation(msg1, msg2);

        msg2->serialize(buffer);

        std::cout << "runServerDevice: I'm sending " << *msg2 << std::endl;

        send(newsockfd, buffer, device->getPuf()->getResponseByteLength()*2, 0);

        free(msg1);
        free(msg2);
        close(newsockfd);
      }else if(n == device->getPuf()->getResponseByteLength()*2){
          Msg3* msg3 = new Msg3(buffer, device->getPuf()->getResponseByteLength());
          std::cout << "runServerDevice: I'm receiving " << *msg3 << std::endl;
          device->verifierCompletion(msg3);
      }else if(n == device->getPuf()->getResponseByteLength()){
        std::cout << "runServerDevice: I'm receiving ";
        printHexBuffer(buffer, device->getPuf()->getResponseByteLength());
        std::cout << std::endl;
        if(device->authentication(buffer, buffer)){
          std::cout << "runServerDevice: I'm sending ";
          printHexBuffer(buffer, device->getPuf()->getResponseByteLength());
          std::cout << std::endl;
          send(newsockfd, buffer, device->getPuf()->getResponseByteLength(), 0);
          close(newsockfd);
        } else {
          std::cerr << "Authentication from verifier failed" << std::endl;
        }

    }
      free(buffer);
      close(sockfd);
    }
  }

  phemap::DeviceServer::~DeviceServer (){

  }
