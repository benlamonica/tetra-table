//
//  T.h
//  tetris
//
//  Created by Ben La Monica on 1/13/15.
//  Copyright (c) 2015 Benjamin Alan La Monica. All rights reserved.
//

#ifndef __tetris__T__
#define __tetris__T__

#include <stdio.h>
#include "TetrisPiece.hpp"

class T : public TetrisPiece {
public:
    T();
    virtual ~T();
    virtual void getMask(int &width, int &height, char *mask) override;
    
};
#endif /* defined(__tetris__T__) */
