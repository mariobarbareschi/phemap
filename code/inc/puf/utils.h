//===- utils.h ----------------------------------------------------*- C -*-===//
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
/// \file utils.h
/// \author Mario Barbareschi
/// \brief This file defines some utilities
//===----------------------------------------------------------------------===//

#ifndef utils_h
#define utils_h

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

unsigned char* xorVector(unsigned char*, const unsigned char*, const unsigned char*, int);
void getRandomNonce(unsigned char*, int);
void printHexBuffer(const unsigned char*, int);


#endif /* utils_h */
