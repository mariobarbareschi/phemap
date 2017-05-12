//===- pufChain.h ----------------------------------------------------*- C++ -*-===//
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
/// \file pufChain.h
/// \author Mario Barbareschi
/// \brief This file defines the header of the PufChain class
//===----------------------------------------------------------------------===//


#ifndef pufChain_h
#define pufChain_h

#include "puf.h"

namespace phemap{
    class PufChain;
};

class phemap::PufChain{
protected:
  int rowCounter = 0;
  int CRByteLength = 0;
public:
  int getCRByteLength();
  void setCRByteLength(int);
  virtual bool getNextLink(puf_t*) = 0;
  virtual bool peekLink(puf_t*, int) = 0;
};


#endif /* pufChain_h */
