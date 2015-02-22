//
//  Z.h
//  tetris
//
//  Created by Ben La Monica on 1/13/15.
//  Copyright (c) 2015 Benjamin Alan La Monica. All rights reserved.
//

#ifndef __tetris__Z__
#define __tetris__Z__

#include <stdio.h>
#include "TetrisPiece.hpp"

class Z : public TetrisPiece {
public:
    Z();
    virtual ~Z();

private:
    typedef TetrisPiece super;
    
};
#endif /* defined(__tetris__Z__) */
