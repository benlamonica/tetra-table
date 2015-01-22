//
//  I.cpp
//  tetris
//
//  Created by Ben La Monica on 1/13/15.
//  Copyright (c) 2015 Benjamin Alan La Monica. All rights reserved.
//

#include "I.hpp"

/*
 ████████
 
 ██
 ██
 ██
 ██
*/

I::I() : super('I', 0x3A, 0xF0, 0xF1, 1, 4){
    
}

I::~I() {
    
}

void I::getMask(char *mask) {
    if (m_rotation == 0 || m_rotation == 180) {
        strcpy(mask, "||||");
    } else if (m_rotation == 90 || m_rotation == 270) {
        strcpy(mask, "||||");
    }
}