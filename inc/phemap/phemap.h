//
//  phemap.h
//  phemap
//
//  Created by Mario Barbareschi on 27/04/17.
//  Copyright © 2017 Mario Barbareschi. All rights reserved.
//

#ifndef phemap_h
#define phemap_h

#include "puf.h"

#define DEFAULT_SENTINEL 4
#define DEFAULT_PUF_LENGTH 16

namespace phemap{
      enum DeviceState {DISCONNECTED, INITIATED, AUTHENTICATED, UNKNOWN, UNSAFE, ERROR};

      typedef struct msg1{
        puf_t* li, *v1, *v2;
      } msg1_t;

      typedef struct msg2{
        puf_t* d1, *d2;
      } msg2_t;
}

#endif /* phemap_h */
