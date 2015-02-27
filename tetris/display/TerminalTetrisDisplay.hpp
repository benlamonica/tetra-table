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
    TerminalTetrisDisplay(int boardWidth, int boardHeight);
    virtual ~TerminalTetrisDisplay();
    virtual void flush() override;
    virtual void drawNextPiece(TetrisPiece::Ptr nextPiece) override;
    virtual void drawScore(int score) override;
    virtual void drawLevel(int level) override;
    virtual void drawRemainingLines(int remainingLines) override;

protected:
    virtual void drawPoint(int x, int y, char ch, const Color& color) override;
private:
    CursesUtil &m_curses;
    int m_xOffset;
    int m_yOffset;
};

#endif /* defined(__tetris__TerminalTetrisDisplay__) */
