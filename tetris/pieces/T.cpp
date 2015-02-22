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


T::T() : super(std::vector<std::string>({" T TTT", "T TTT ", "TTT T ", " TTT T"}), 'T', 0xA1, 0, 0xF1, 3, 2){
    
}

T::~T() {
    
}