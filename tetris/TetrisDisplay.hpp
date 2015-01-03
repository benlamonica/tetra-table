//
//  TetrisDisplay.hpp
//  tetris
//
//  Created by La Monica Family on 12/28/14.
//  Copyright (c) 2014 Benjamin Alan La Monica. All rights reserved.
//

#ifndef tetris_TetrisDisplay_hpp
#define tetris_TetrisDisplay_hpp

#include "TetrisPiece.hpp"

class TetrisDisplay {
public:
    void drawBoard(char **board, TetrisPiece::Ptr currentPiece);
};

#endif
