//
//  Z.cpp
//  tetris
//
//  Created by Ben La Monica on 1/13/15.
//  Copyright (c) 2015 Benjamin Alan La Monica. All rights reserved.
//

#include "Z.hpp"

/*
 ████
   ████
 
   ██
 ████
 ██
*/

Z::Z() : super('Z', 0xF1, 0x10, 0, 3, 2) {
    
}

Z::~Z() {
    
}

void Z::getMask(char *mask) {
    if (m_rotation == 0 || m_rotation == 180) {
        strcpy(mask, "ZZ  ZZ");
    } else if (m_rotation == 90 || m_rotation == 270) {
        strcpy(mask, " ZZZZ ");
    }
}
