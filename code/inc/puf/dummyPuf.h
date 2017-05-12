//===- dummyPuf.h ----------------------------------------------------*- C++ -*-===//
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
/// \file dummyPuf.h
/// \author Mario Barbareschi
/// \brief This file defines the header of the DummyPuf class
//===----------------------------------------------------------------------===//

#ifndef dummyPuf_h
#define dummyPuf_h

#include <iostream>

#include "puf.h"

#define PUF_BYTE_LENGTH 16

namespace phemap{
    class DummyPuf;
}

class phemap::DummyPuf : public phemap::Puf{
private:
    puf_t* seed;
public:
    DummyPuf ();
    DummyPuf (puf_t* seed);
    ~DummyPuf ();
    void setSeed(const puf_t*);
    const puf_t* getSeed(puf_t*);
    /*Override methods*/
    int getResponseByteLength();
    int getChallengeByteLength();
    void generateResponse(const puf_t*, puf_t*);
};

#endif /* dummyPuf_h */
