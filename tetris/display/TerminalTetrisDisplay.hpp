//
//  TerminalTetrisDisplay.h
//  tetris
//
//  Created by Ben La Monica on 2/17/15.
//  Copyright (c) 2015 Benjamin Alan La Monica. All rights reserved.
//

#ifndef __tetris__TerminalTetrisDisplay__
#define __tetris__TerminalTetrisDisplay__

#include <stdio.h>
#include "TetrisDisplay.hpp"
#include "CursesUtil.hpp"

class TerminalTetrisDisplay : public TetrisDisplay {
public:
    TerminalTetrisDisplay();
    virtual ~TerminalTetrisDisplay();
protected:
    virtual void drawPoint(int x, int y, char ch, const Color& color) override;
private:
    CursesUtil &m_curses;
};

#endif /* defined(__tetris__TerminalTetrisDisplay__) */