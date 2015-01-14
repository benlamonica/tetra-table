//
//  Q.cpp
//  tetris
//
//  Created by Ben La Monica on 1/13/15.
//  Copyright (c) 2015 Benjamin Alan La Monica. All rights reserved.
//

#include "Q.hpp"

/*
 ████
 ████
*/

Q::Q() {
    
}

Q::~Q() {
    
}

void Q::getMask(int &width, int &height, char *mask) {
    width = 2;
    height = 2;
    strcpy(mask, "QQQQ");
}
