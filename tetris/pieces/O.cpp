//
//  O.cpp
//  tetris
//
//  Created by Ben La Monica on 1/13/15.
//  Copyright (c) 2015 Benjamin Alan La Monica. All rights reserved.
//

#include "O.hpp"

/*
 ████
 ████
*/

O::O() : super(std::vector<std::string>({"OOOO"}), 'O', Color(0xF1, 0xF1, 0), Color(0x76,0x76,0x76), 2) {
    
}

O::~O() {
    
}
