//===- utils.c ----------------------------------------------------*- C -*-===//
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
/// \file utils.c
/// \author Mario Barbareschi
/// \brief This file implements some utilities
//===----------------------------------------------------------------------===//

#include "utils.h"

unsigned char* xorVector(unsigned char* o, const unsigned char* x, const unsigned char* y, int length){
    int i;
    for(i = 0; i < length; i++)
        o[i] = x[i]^y[i];
      return o;
}

void getRandomNonce(unsigned char* nonce, int length){
 	struct timeval time;
 	gettimeofday(&time,NULL);
 	srand((time.tv_sec * 1000) + (time.tv_usec / 1000));
 	int i;
 	for(i = 0; i < length; i++)
      		nonce[i] = rand();
}

void printHexBuffer(const unsigned char* r, int length){
  printf("0x");
  int i;
  for(i=0; i<length; i++)
    printf("%02X", r[i]);
  printf("\n");
}
