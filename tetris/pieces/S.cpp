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

S::S() : super(std::vector<std::string>({" SSSS ", "S SS S", " SSSS ", "S SS S"}), 'S', 0x3B, 0xF1, 0, 3, 2) {
    
}

S::~S() {
    
}