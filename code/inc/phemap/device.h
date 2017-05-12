//===- device.h ----------------------------------------------------*- C++ -*-===//
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
/// \file device.h
/// \author Mario Barbareschi
/// \brief This file defines the header of the Device class
//===----------------------------------------------------------------------===//

#ifndef device_h
#define device_h

#include "deviceSkeleton.h"
#include "verifierProxy.h"

namespace phemap{
    class Device;
}

class phemap::Device : public phemap::DeviceSkeleton{
protected:
    phemap::Puf* puf;
    puf_t* storage;
    VerifierProxy* verifierProxy;
public:
    Device (std::string, phemap::Puf*);
    Device (std::string, phemap::Puf*, int);
    phemap::Puf* getPuf(void);
    phemap::Device* setPuf(phemap::Puf*);
    void getNextPufLink(puf_t*, bool);
    bool verifyCRP(const puf_t*, const puf_t*);
    bool verifyCRPWithSentinel(const puf_t*, const puf_t*);
    void flushStorage();
    phemap::Device* setStorage(puf_t*);
    bool verifierInitiation(const phemap::Msg1*, phemap::Msg2*);
    bool verifierCompletion(const phemap::Msg3*);
    bool authentication(const puf_t*, puf_t*);
    bool authenticateVerifier(void);
    ~Device ();

};

#endif /* device_h */
