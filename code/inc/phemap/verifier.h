//===- verifier.h ----------------------------------------------------*- C++ -*-===//
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
/// \file verifier.h
/// \author Mario Barbareschi
/// \brief This file defines the header of the Verifier class
//===----------------------------------------------------------------------===//


#ifndef verifier_h
#define verifier_h

#include <iostream>
#include <string>
#include <map>
#include <unordered_map>

#include "phemap.h"
#include "deviceManager.h"
#include "verifierSkeleton.h"

typedef std::unordered_map<std::string, phemap::DeviceManager*> DevicesMap_t;

namespace phemap{
    class Verifier;
}

class phemap::Verifier : public phemap::VerifierSkeleton{
protected:
    DevicesMap_t* devicesMap;
public:
    Verifier (int CRByteLength);
    DevicesMap_t* getDevicesMap(void);
    bool verifierInitiation(std::string);
    bool verifierAuthentication(std::string);
    bool authentication(const std::string, const puf_t*, puf_t*);

    ~Verifier ();
};

#endif /* verifier_h */
