//
//  Two.cpp
//  tetris
//
//  Created by Ben La Monica on 1/13/15.
//  Copyright (c) 2015 Benjamin Alan La Monica. All rights reserved.
//

#include "Two.hpp"

/*
 ████
   ████
 
   ██
 ████
 ██
*/

Two::Two() {
    
}

Two::~Two() {
    
}

void Two::getMask(int &width, int &height, char *mask) {
    if (m_rotation == 0 || m_rotation == 180) {
        width = 3;
        height = 2;
        strcpy(mask, "22  22");
    } else if (m_rotation == 90 || m_rotation == 279) {
        width = 2;
        height = 3;
        strcpy(mask, " 2222 ");
    }
}
