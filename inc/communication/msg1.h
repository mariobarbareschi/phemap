//===- msg1.h ----------------------------------------------------*- C++ -*-===//
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
/// \file msg1.h
/// \author Mario Barbareschi
/// \brief This file defines the header of the Msg1 class
//===----------------------------------------------------------------------===//

#ifndef msg1_h
#define msg1_h

#include <iostream>

#include "phemap.h"
#include "puf.h"
#include "utils.h"

namespace phemap{
    class Msg1;
}

class phemap::Msg1{
protected:
    puf_t* li, *v1, *v2;
    int pufLength;
public:
    Msg1 ();
    Msg1 (int);
    Msg1 (puf_t*, int);
    Msg1* setLi(puf_t*);
    Msg1* setV1(puf_t*);
    Msg1* setV2(puf_t*);
    puf_t* getLi(void) const;
    puf_t* getV1(void) const;
    puf_t* getV2(void) const;
    void getLi(puf_t*) const;
    void getV1(puf_t*) const;
    void getV2(puf_t*) const;
    int getPufLength(void) const;
    int serialize(puf_t*) const;
    bool deserialize(puf_t*, int);

    friend std::ostream& operator<<(std::ostream&, const Msg1&);

    ~Msg1 ();
};

#endif /* msg1_h */
