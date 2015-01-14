//
//  Line.cpp
//  tetris
//
//  Created by Ben La Monica on 1/13/15.
//  Copyright (c) 2015 Benjamin Alan La Monica. All rights reserved.
//

#include "Line.hpp"

/*
 ████████
 
 ██
 ██
 ██
 ██
*/

Line::Line() {
    
}

Line::~Line() {
    
}

void Line::getMask(int &width, int &height, char *mask) {
    if (m_rotation == 0 || m_rotation == 180) {
        width = 1;
        height = 4;
        strcpy(mask, "||||");
    } else if (m_rotation == 90 || m_rotation == 270) {
        width = 4;
        height = 1;
        strcpy(mask, "||||");
    }
}