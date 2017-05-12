//===- deviceManager.h ----------------------------------------------------*- C++ -*-===//
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
/// \file deviceManager.h
/// \author Mario Barbareschi
/// \brief This file defines the header of the DeviceManager class
//===----------------------------------------------------------------------===//

#ifndef deviceManager_h
#define deviceManager_h

#include "phemap.h"
#include "deviceProxy.h"
#include "authenticateSkeleton.h"

namespace phemap{
    class DeviceManager;
}

class phemap::DeviceManager {
protected:
    phemap::DeviceProxy* device;
public:
    DeviceManager() {};
    DeviceManager(phemap::DeviceProxy*);
    DeviceManager* setDeviceProxy(phemap::DeviceProxy*);
    bool init(void);
    bool authenticateDevice(void);
    bool authentication(const puf_t*, puf_t*);
    void getNextPufLink(puf_t*, bool);
    void peekNextPufLink(puf_t*, bool);
    //~DeviceManager ();

};

#endif /* deviceManager_h */
