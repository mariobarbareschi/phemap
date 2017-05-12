//
//  authenticateSkeleton.h
//  phemap
//
//  Created by Mario Barbareschi on 27/04/17.
//  Copyright © 2017 Mario Barbareschi. All rights reserved.
//

#ifndef authenticateSkeleton_h
#define authenticateSkeleton_h

#include <string>

#include "phemap.h"

namespace phemap{
    class AuthenticateSkeleton;
}

class phemap::AuthenticateSkeleton{
public:
    AuthenticateSkeleton () {};
    virtual bool authentication(const puf_t*, puf_t*) = 0;
    virtual ~AuthenticateSkeleton () {};
};

#endif /* authenticateSkeleton_h */
