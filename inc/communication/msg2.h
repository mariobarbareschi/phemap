//===- msg2.h ----------------------------------------------------*- C++ -*-===//
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
/// \file msg2.h
/// \author Mario Barbareschi
/// \brief This file defines the header of the Msg2 class
//===----------------------------------------------------------------------===//

#ifndef msg2_h
#define msg2_h

#include <iostream>

#include "phemap.h"
#include "puf.h"

namespace phemap{
    class Msg2;
}

class phemap::Msg2{
protected:
    puf_t *d1, *d2;
    int pufLength;
public:
    Msg2 ();
    Msg2 (int);
    Msg2 (puf_t*, int);
    Msg2* setD1(puf_t*);
    Msg2* setD2(puf_t*);
    puf_t* getD1(void) const;
    puf_t* getD2(void) const;
    void getD1(puf_t*) const;
    void getD2(puf_t*) const;
    int getPufLength(void) const;
    int serialize(puf_t*) const;
    bool deserialize(puf_t*, int);

    friend std::ostream& operator<<(std::ostream&, const Msg2&);

    ~Msg2 ();
};

#endif /* msg2_h */
