//
//  KeyboardTetrisInput.h
//  tetris
//
//  Created by La Monica Family on 1/2/15.
//  Copyright (c) 2015 Benjamin Alan La Monica. All rights reserved.
//

#ifndef __tetris__KeyboardTetrisInput__
#define __tetris__KeyboardTetrisInput__

#include <stdio.h>

#include "TetrisInput.hpp"
#include "CursesUtil.hpp"

class KeyboardTetrisInput : public TetrisInput {
public:
    KeyboardTetrisInput(Tetris *game);
    virtual ~KeyboardTetrisInput();
protected:
    virtual Move getNextMove() override;
private:
    CursesUtil& m_curses;
    typedef TetrisInput super;
};
#endif /* defined(__tetris__KeyboardTetrisInput__) */
