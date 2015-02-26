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

I::I() : super(std::vector<std::string>({"    IIII        ", "  I   I   I   I ", "        IIII    ", " I   I   I   I  "}), 'I', Color(0x3A, 0xF0, 0xF1), Color(0x62,0x62,0x62), 4){
    
}

I::~I() {
    
}