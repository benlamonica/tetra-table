//
//  T.cpp
//  tetris
//
//  Created by Ben La Monica on 1/13/15.
//  Copyright (c) 2015 Benjamin Alan La Monica. All rights reserved.
//

#include "T.hpp"

/*

   ██
 ██████

 ██
 ████
 ██
 
 ██████
   ██
 
   ██
 ████
   ██
 
*/


T::T() {
    
}

T::~T() {
    
}

void T::getMask(int &width, int &height, char *mask) {
    if (m_rotation == 0) {
        width = 3;
        height = 2;
        strcpy(mask, " T TTT");
    } else if (m_rotation == 90) {
        width = 2;
        height = 3;
        strcpy(mask, "T TTT ");
    } else if (m_rotation == 180) {
        width = 3;
        height = 2;
        strcpy(mask, "TTT T ");
    } else if (m_rotation == 270) {
        width = 2;
        height = 3;
        strcpy(mask, " TTT T");
    }
}