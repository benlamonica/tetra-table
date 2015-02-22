//
//  J.h
//  tetris
//
//  Created by Ben La Monica on 1/13/15.
//  Copyright (c) 2015 Benjamin Alan La Monica. All rights reserved.
//

#ifndef __tetris__J__
#define __tetris__J__

#include <stdio.h>
#include "TetrisPiece.hpp"

class J : public TetrisPiece {
public:
    J();
    virtual ~J();
    
private:
    typedef TetrisPiece super;
    
};
#endif /* defined(__tetris__J__) */
