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

I::I() : super(std::vector<std::string>({"IIII", "IIII", "IIII", "IIII"}), 'I', 0x3A, 0xF0, 0xF1, 4, 1){
    
}

I::~I() {
    
}