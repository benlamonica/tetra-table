//
//  S.cpp
//  tetris
//
//  Created by Ben La Monica on 1/13/15.
//  Copyright (c) 2015 Benjamin Alan La Monica. All rights reserved.
//

#include "S.hpp"

/*
  ████
████

██
████
  ██
 
*/

S::S() : super('S', 0x3B, 0xF1, 0, 3, 2) {
    
}

S::~S() {
    
}

void S::getMask(char *mask) {
    if (m_rotation == 0 || m_rotation == 180) {
        strcpy(mask, " SSSS ");
    } else if (m_rotation == 90 || m_rotation == 270) {
        strcpy(mask, "S SS S");
    }
}
