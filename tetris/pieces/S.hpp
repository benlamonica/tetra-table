//
//  S.hpp
//  tetris
//
//  Created by Ben La Monica on 1/13/15.
//  Copyright (c) 2015 Benjamin Alan La Monica. All rights reserved.
//

#ifndef __tetris__S__
#define __tetris__S__

#include <stdio.h>
#include "TetrisPiece.hpp"

class S : public TetrisPiece {
public:
    S();
    virtual ~S();
    virtual void getMask(char *mask) override;
  
private:
    typedef TetrisPiece super;

};
#endif /* defined(__tetris__S__) */
