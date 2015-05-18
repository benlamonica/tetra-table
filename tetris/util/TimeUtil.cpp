//
//  TimeUtil.cpp
//  TetraTable
//
//  Created by Ben La Monica on 5/5/15.
//  Copyright (c) 2015 Benjamin Alan La Monica. All rights reserved.
//

#include "TimeUtil.hpp"

namespace util {
    int64_t now() {
        using namespace std::chrono;
        return duration_cast<nanoseconds>(high_resolution_clock::now().time_since_epoch()).count();
    }
    
    void millisleep(int millis) {
        struct timespec sleepTime = {(millis / 1000), (millis % 1000) * 1000000};
        nanosleep(&sleepTime, NULL);
    }
}