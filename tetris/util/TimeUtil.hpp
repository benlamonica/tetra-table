//
//  TimeUtil.hpp
//  tetris
//
//  Created by Ben La Monica on 4/13/15.
//  Copyright (c) 2015 Benjamin Alan La Monica. All rights reserved.
//

#ifndef tetris_TimeUtil_hpp
#define tetris_TimeUtil_hpp

#include <chrono>

namespace tetris {
    namespace TimeUtil {
        int64_t now();
        void millisleep(int millis);
    }
}

#endif
