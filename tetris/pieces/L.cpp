//
//  L.cpp
//  tetris
//
//  Created by Ben La Monica on 1/13/15.
//  Copyright (c) 2015 Benjamin Alan La Monica. All rights reserved.
//

#include "L.hpp"

/*
 
 ██
 ██
 ████
 
 ██████
 ██
 
 ████
   ██
   ██
 
     ██
 ██████

*/

L::L() {
    
}

L::~L() {
    
}

void L::getMask(int &width, int &height, char *mask) {
    if (m_rotation == 0) {
        width = 3;
        height = 2;
        strcpy(mask, "L L LL");
    } else if (m_rotation == 90) {
        width = 2;
        height = 3;
        strcpy(mask, "LLLL  ");
    } else if (m_rotation == 180) {
        width = 3;
        height = 2;
        strcpy(mask, "LL L L");
    } else if (m_rotation == 270) {
        width = 2;
        height = 3;
        strcpy(mask, "  LLLL");
    }
}
