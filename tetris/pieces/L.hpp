//
//  L.h
//  tetris
//
//  Created by Ben La Monica on 1/13/15.
//  Copyright (c) 2015 Benjamin Alan La Monica. All rights reserved.
//

#ifndef __tetris__L__
#define __tetris__L__

#include <stdio.h>
#include "TetrisPiece.hpp"

class L : public TetrisPiece {
public:
    L();
    virtual ~L();

private:
    typedef TetrisPiece super;

};
#endif /* defined(__tetris__L__) */
