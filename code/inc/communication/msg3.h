//===- msg3.h ----------------------------------------------------*- C++ -*-===//
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
/// \file msg3.h
/// \author Mario Barbareschi
/// \brief This file defines the header of the Msg3 class
//===----------------------------------------------------------------------===//

#ifndef msg3_h
#define msg3_h

#include <iostream>

#include "phemap.h"
#include "puf.h"

namespace phemap{
    class Msg3;
}

class phemap::Msg3{
protected:
    puf_t *li, *v3;
    int pufLength;
public:
    Msg3 ();
    Msg3 (int);
    Msg3 (puf_t*, int);
    Msg3* setLi(puf_t*);
    Msg3* setV3(puf_t*);
    puf_t* getLi(void) const;
    puf_t* getV3(void) const;
    void getLi(puf_t*) const;
    void getV3(puf_t*) const;
    int getPufLength(void) const;
    int serialize(puf_t*) const;
    bool deserialize(puf_t*, int);

    friend std::ostream& operator<<(std::ostream&, const Msg3&);

    ~Msg3 ();
};

#endif /* msg3_h */
