//
//  Line.h
//  tetris
//
//  Created by Ben La Monica on 1/13/15.
//  Copyright (c) 2015 Benjamin Alan La Monica. All rights reserved.
//

#ifndef __tetris__Line__
#define __tetris__Line__

#include <stdio.h>
#include "TetrisPiece.hpp"

class Line : public TetrisPiece {
public:
    Line();
    virtual ~Line();
    virtual void getMask(int &width, int &height, char *mask) override;

};

#endif /* defined(__tetris__Line__) */
