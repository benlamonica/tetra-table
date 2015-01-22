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


T::T() : super('T', 0xA1, 0, 0xF1, 3, 2){
    
}

T::~T() {
    
}

void T::getMask(char *mask) {
    if (m_rotation == 0) {
        strcpy(mask, " T TTT");
    } else if (m_rotation == 90) {
        strcpy(mask, "T TTT ");
    } else if (m_rotation == 180) {
        strcpy(mask, "TTT T ");
    } else if (m_rotation == 270) {
        strcpy(mask, " TTT T");
    }
}