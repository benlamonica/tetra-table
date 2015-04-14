//
//  TimeUtil.hpp
//  tetris
//
//  Created by Ben La Monica on 4/13/15.
//  Copyright (c) 2015 Benjamin Alan La Monica. All rights reserved.
//

#ifndef tetris_TimeUtil_hpp
#define tetris_TimeUtil_hpp

namespace tetris {
    namespace TimeUtil {
        int64_t now() {
            using namespace std::chrono;
            return duration_cast<milliseconds>(high_resolution_clock::now().time_since_epoch()).count();
        }
        
        void millisleep(int millis) {
            struct timespec sleepTime = {(millis / 1000), (millis % 1000) * 1000000};
            nanosleep(&sleepTime, NULL);
        }
    }
}

#endif
