//
//  Q.hpp
//  tetris
//
//  Created by Ben La Monica on 1/13/15.
//  Copyright (c) 2015 Benjamin Alan La Monica. All rights reserved.
//

#ifndef __tetris__Q__
#define __tetris__Q__

#include <stdio.h>
#include "TetrisPiece.hpp"

class Q : public TetrisPiece {
public:
    Q();
    virtual ~Q();
    virtual void getMask(int &width, int &height, char *mask) override;
    
};
#endif /* defined(__tetris__Q__) */
