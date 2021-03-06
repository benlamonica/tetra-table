//
//  TerminalDisplay.cpp
//  TetraTable
//
//  Created by Ben La Monica on 2/17/15.
//  Copyright (c) 2015 Benjamin Alan La Monica. All rights reserved.
//

#include "TerminalDisplay.hpp"
#include "../util/CursesUtil.hpp"
#include "../util/TimeUtil.hpp"
#include <curses.h>
#include <exception>

TerminalDisplay::TerminalDisplay(int boardWidth, int boardHeight) : m_curses(CursesUtil::instance()), m_xOffset(2), m_yOffset(1) {
    // draw a border around the playing field..only necessary in terminal mode, not table mode
    Color borderColor(0x30,0x30,0x30);
    for (int i = 0; i < 24; i++) {
        m_curses.draw(i,0,' ', borderColor);
    }
    for (int i = 0; i < 22; i++) {
        m_curses.draw(0,i,' ',borderColor);
        m_curses.draw(1,i,' ',borderColor);
        m_curses.draw(22,i,' ',borderColor);
        m_curses.draw(23,i,' ',borderColor);
    }
    for (int i = 0; i < 24; i++) {
        m_curses.draw(i,boardHeight+1,' ', borderColor);
    }
}

TerminalDisplay::~TerminalDisplay() {
    
}

void TerminalDisplay::redraw() {
    m_curses.redraw();
}

void TerminalDisplay::drawNextPiece(TetraTablePiece::Ptr nextPiece) {
    drawPiece(nextPiece, 12, 2);
}

void TerminalDisplay::drawHeldPiece(TetraTablePiece::Ptr heldPiece) {
    drawPiece(heldPiece, 12, 8);
}

void TerminalDisplay::drawScore(int score) {
    m_curses.print(25,21,"Score : " + std::to_string(score) + "           ");
}

void TerminalDisplay::drawLevel(int level) {
    m_curses.print(25,20,"Level : " + std::to_string(level) + "   ");
}

void TerminalDisplay::drawRemainingLines(int remainingLines) {
    m_curses.print(25, 19, "Lines Remaining : " + std::to_string(remainingLines) + "     ");
}

void TerminalDisplay::flush() {
    m_curses.flush();
    util::millisleep(5);
}

void TerminalDisplay::drawPoint(int x, int y, char ch, const Color& color) {
    m_curses.draw(x*2 + m_xOffset,y + m_yOffset,ch,color);
    m_curses.draw(x*2+1 + m_xOffset,y + m_yOffset,ch,color);
}
