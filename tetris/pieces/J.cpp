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

J::J() : super(std::vector<std::string>({"J  JJJ", "JJ J J ", "JJJ  J", " J JJJ"}), 'J', 0, 0, 0xF0, 3, 2) {
    
}

J::~J() {
    
}