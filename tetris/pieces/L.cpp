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

L::L() : super('L', 0xF1, 0xA1, 0, 2, 3){
    
}

L::~L() {
    
}

void L::getMask(char *mask) {
    if (m_rotation == 0) {
        strcpy(mask, "L L LL");
    } else if (m_rotation == 90) {
        strcpy(mask, "LLLL  ");
    } else if (m_rotation == 180) {
        strcpy(mask, "LL L L");
    } else if (m_rotation == 270) {
        strcpy(mask, "  LLLL");
    }
}
