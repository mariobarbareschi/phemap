//===- pufChainFromFile.cpp ----------------------------------------------------*- C++ -*-===//
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
/// \file pufChainFromFile.cpp
/// \author Mario Barbareschi
/// \brief This file defines the implementation of the PufChainFromFile class
//===----------------------------------------------------------------------===//

#include "pufChainFromFile.h"
#include <assert.h>
#include <stdlib.h>     /* strtol */


phemap::PufChainFromFile::PufChainFromFile(std::string filename){
  assert(filename.length() > 0 && "Unvalid string");
  this->filename = filename;
  pufChainFile = new std::ifstream(filename);
  if(pufChainFile->is_open()){
    std::getline(*pufChainFile, nextLink);
    assert(nextLink.length()%2 == 0 && "Unvalid string for PUF response");
    setCRByteLength(nextLink.length()/2);
    pufChainFile->clear();
    pufChainFile->seekg(0, std::ios::beg);
    rowCounter = 0;
  }else{
    std::cerr << "Unable to open file: " << filename << std::endl;
  }
}

bool phemap::PufChainFromFile::getNextLink(puf_t* nextLink){
  //getline(*pufChainFile, this->nextLink);
  (*pufChainFile) >> this->nextLink;
  rowCounter++;
  for(int i = 0; i < getCRByteLength(); i++){
    nextLink[i] = strtol(this->nextLink.substr(2*i,2).data(), NULL, 16);
  }
  return pufChainFile->eof();
}

bool phemap::PufChainFromFile::peekLink(puf_t* nextLink, int distance){
  std::string links;
  do{
    (*pufChainFile) >> links;
  }while(--distance > 0);
  for(int i = 0; i < getCRByteLength(); i++){
    nextLink[i] = strtol(links.substr(2*i,2).data(), NULL, 16);
  }
  bool testEof = pufChainFile->eof();

  pufChainFile->clear();
  pufChainFile->seekg(0, std::ios::beg);
  for(int i=0; i < rowCounter; ++i) pufChainFile->ignore(std::numeric_limits<std::streamsize>::max(),'\n');
  return testEof;
}


phemap::PufChainFromFile::~PufChainFromFile(){
  pufChainFile->close();
  free(pufChainFile);

}
