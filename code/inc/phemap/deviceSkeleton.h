//===- deviceSkeleton.h ----------------------------------------------------*- C++ -*-===//
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
/// \file deviceSkeleton.h
/// \author Mario Barbareschi
/// \brief This file defines the abstract class DeviceSkeleton
//===----------------------------------------------------------------------===//

#ifndef deviceSkeleton_h
#define deviceSkeleton_h

#include <string>

#include "phemap.h"
#include "authenticateSkeleton.h"
#include "msg1.h"
#include "msg2.h"
#include "msg3.h"

#define DEVICE_PORT_NUMBER 9876

namespace phemap{
    class DeviceSkeleton;
}

class phemap::DeviceSkeleton : public AuthenticateSkeleton{
private:
    std::string deviceID;
protected:
  phemap::DeviceState state;
  int sentinel;
  int linkCounter;
public:
    DeviceSkeleton ();
    DeviceSkeleton (std::string);
    DeviceSkeleton (std::string, int);
    phemap::DeviceSkeleton* setDeviceID(std::string);
    std::string getDeviceID(void);
    phemap::DeviceSkeleton* setSentinel(int);
    int getSentinel(void);
    phemap::DeviceState getState();
    phemap::DeviceSkeleton* setState(phemap::DeviceState);
    bool countLink(bool);
    void resetlinkCounter();
    virtual void getNextPufLink(puf_t*, bool) = 0;
    virtual bool verifierInitiation(const Msg1*, Msg2*) = 0;
    virtual bool verifierCompletion(const Msg3*) = 0;
    virtual bool authentication(const puf_t*, puf_t*) = 0;
    virtual ~DeviceSkeleton () {};
};

#endif /* deviceSkeleton_h */
