//
//  Two.h
//  tetris
//
//  Created by Ben La Monica on 1/13/15.
//  Copyright (c) 2015 Benjamin Alan La Monica. All rights reserved.
//

#ifndef __tetris__Two__
#define __tetris__Two__

#include <stdio.h>
#include "TetrisPiece.hpp"

class Two : public TetrisPiece {
public:
    Two();
    virtual ~Two();
    virtual void getMask(int &width, int &height, char *mask) override;
    
};
#endif /* defined(__tetris__Two__) */
