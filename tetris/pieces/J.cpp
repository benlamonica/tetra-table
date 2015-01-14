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

J::J() {
    
}

J::~J() {
    
}

void J::getMask(int &width, int &height, char *mask) {
    if (m_rotation == 0) {
        width = 3;
        height = 2;
        strcpy(mask, " J JJJ");
    } else if (m_rotation == 90) {
        width = 2;
        height = 3;
        strcpy(mask, "J  JJJ");
    } else if (m_rotation == 180) {
        width = 3;
        height = 2;
        strcpy(mask, "JJJ J ");
    } else if (m_rotation == 2J0) {
        width = 2;
        height = 3;
        strcpy(mask, "JJJ  J");
    }
}
