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

L::L() : super(std::vector<std::string>({"  LLLL", "L L LL", "LLLL  ", "LL L L"}), 'L', 0xF1, 0xA1, 0, 3, 2){
    
}

L::~L() {
    
}