//
//  O.cpp
//  tetris
//
//  Created by Ben La Monica on 1/13/15.
//  Copyright (c) 2015 Benjamin Alan La Monica. All rights reserved.
//

#include "O.hpp"

/*
 ████
 ████
*/

O::O() : super('0', 0xF1, 0xF1, 0, 2, 2) {
    
}

O::~O() {
    
}

void O::getMask(char *mask) {
    strcpy(mask, "OOOO");
}
