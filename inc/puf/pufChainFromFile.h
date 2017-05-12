//===- pufChainFromFile.h ----------------------------------------------------*- C++ -*-===//
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
/// \file pufChainFromFile.h
/// \author Mario Barbareschi
/// \brief This file defines the header of the PufChainFromFile class
//===----------------------------------------------------------------------===//


#ifndef pufChainFromFile_h
#define pufChainFromFile_h

#include <iostream>
#include <fstream>
#include <string>

#include "pufChain.h"

namespace phemap{
    class PufChainFromFile;
};

class phemap::PufChainFromFile : public phemap::PufChain{
private:
  std::ifstream *pufChainFile;
protected:
  std::string filename;
  std::string nextLink;
public:
  PufChainFromFile(std::string);
  bool getNextLink(puf_t*);
  bool peekLink(puf_t*, int);
  ~PufChainFromFile();
};


#endif /* pufChainFromFile_h */
