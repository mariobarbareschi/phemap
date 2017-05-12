//===- verifierSkeleton.h ----------------------------------------------------*- C++ -*-===//
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
/// \file verifierSkeleton.h
/// \author Mario Barbareschi
/// \brief This file defines the abstract class VerifierSkeleton
//===----------------------------------------------------------------------===//


#ifndef verifierSkeleton_h
#define verifierSkeleton_h

#include <iostream>
#include <string>

#include "phemap.h"

#define VERIFIER_PORT_NUMBER 8765

namespace phemap{
    class VerifierSkeleton;
}

class phemap::VerifierSkeleton{
protected:
  int CRByteLength = 0;
public:
    VerifierSkeleton (): CRByteLength(0) {};
    VerifierSkeleton (int CRByteLength): CRByteLength(CRByteLength) {};
    int getCRByteLength() {return CRByteLength;}
    VerifierSkeleton* setCRByteLength(int CRByteLength) {this->CRByteLength = CRByteLength; return this;}
    virtual bool authentication(const std::string, const puf_t*, puf_t*) = 0;
    ~VerifierSkeleton (){}
};

#endif /* verifierSkeleton_h */
