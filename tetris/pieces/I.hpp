//
//  I.h
//  tetris
//
//  Created by Ben La Monica on 1/13/15.
//  Copyright (c) 2015 Benjamin Alan La Monica. All rights reserved.
//

#ifndef __tetris__I__
#define __tetris__I__

#include <stdio.h>
#include "TetrisPiece.hpp"

class I : public TetrisPiece {
public:
    I();
    virtual ~I();
    virtual void getMask(char *mask) override;

private:
    typedef TetrisPiece super;

};

#endif /* defined(__tetris__I__) */
