//
//  TerminalDisplay.h
//  TetraTable
//
//  Created by Ben La Monica on 2/17/15.
//  Copyright (c) 2015 Benjamin Alan La Monica. All rights reserved.
//

#ifndef __TetraTable__TerminalDisplay__
#define __TetraTable__TerminalDisplay__

#include <stdio.h>
#include "TetraTableDisplay.hpp"
#include "../util/CursesUtil.hpp"

class TerminalDisplay : public TetraTableDisplay {
public:
    TerminalDisplay(int boardWidth, int boardHeight);
    virtual ~TerminalDisplay();
    virtual void flush() override;
    virtual void drawNextPiece(TetraTablePiece::Ptr nextPiece) override;
    virtual void drawHeldPiece(TetraTablePiece::Ptr heldPiece) override;
    virtual void drawScore(int score) override;
    virtual void drawLevel(int level) override;
    virtual void drawRemainingLines(int remainingLines) override;
    virtual void redraw() override;

protected:
    virtual void drawPoint(int x, int y, char ch, const Color& color) override;
private:
    void drawPiece(TetraTablePiece::Ptr piece, int x, int y);
    CursesUtil &m_curses;
    int m_xOffset;
    int m_yOffset;
};

#endif /* defined(__TetraTable__TerminalDisplay__) */
