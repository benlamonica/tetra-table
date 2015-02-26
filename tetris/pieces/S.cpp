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

S::S() : super(std::vector<std::string>({" SSSS    ", " S  SS  S", "    SSSS ", "S  SS  S "}), 'S', Color(0x3B, 0xF1, 0), Color(0x8a,0x8a,0x8a), 3) {
    
}

S::~S() {
    
}