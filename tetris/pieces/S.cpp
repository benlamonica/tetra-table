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

S::S() {
    
}

S::~S() {
    
}

void S::getMask(int &width, int &height, char *mask) {
    if (m_rotation == 0 || m_rotation == 180) {
        width = 3;
        height = 2;
        strcpy(mask, " SSSS ");
    } else if (m_rotation == 90 || m_rotation == 270) {
        width = 2;
        height = 3;
        strcpy(mask, "S SS S");
    }
}
