//
//  J.cpp
//  tetris
//
//  Created by Ben La Monica on 1/13/15.
//  Copyright (c) 2015 Benjamin Alan La Monica. All rights reserved.
//

#include "J.hpp"

/*
 
   ██
   ██
 ████
 
 ██
 ██████
 
 ████
 ██
 ██
 
 ██████
     ██
 
 */

J::J() : super('J', 0, 0, 0xF0, 2, 3) {
    
}

J::~J() {
    
}

void J::getMask(char *mask) {
    if (m_rotation == 0) {
        strcpy(mask, " J JJJ");
    } else if (m_rotation == 90) {
        strcpy(mask, "J  JJJ");
    } else if (m_rotation == 180) {
        strcpy(mask, "JJJ J ");
    } else if (m_rotation == 270) {
        strcpy(mask, "JJJ  J");
    }
}
