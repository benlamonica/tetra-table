//
//  O.hpp
//  tetris
//
//  Created by Ben La Monica on 1/13/15.
//  Copyright (c) 2015 Benjamin Alan La Monica. All rights reserved.
//

#ifndef __tetris__O__
#define __tetris__O__

#include <stdio.h>
#include "TetrisPiece.hpp"

class O : public TetrisPiece {
public:
    O();
    virtual ~O();
    virtual void getMask(char *mask) override;

private:
    typedef TetrisPiece super;

};
#endif /* defined(__tetris__O__) */
