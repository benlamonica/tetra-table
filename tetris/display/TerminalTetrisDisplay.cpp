//
//  TerminalTetrisDisplay.cpp
//  tetris
//
//  Created by Ben La Monica on 2/17/15.
//  Copyright (c) 2015 Benjamin Alan La Monica. All rights reserved.
//

#include "TerminalTetrisDisplay.hpp"
#include "CursesUtil.hpp"
#include <curses.h>
#include <exception>

TerminalTetrisDisplay::TerminalTetrisDisplay(int boardWidth, int boardHeight) : m_curses(CursesUtil::instance()), m_xOffset(2), m_yOffset(1) {
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

TerminalTetrisDisplay::~TerminalTetrisDisplay() {
    
}

void TerminalTetrisDisplay::drawNextPiece(TetrisPiece::Ptr nextPiece) {
    int width = 3;
    std::string mask = "         ";
    Color c(0,0,0);
    if (nextPiece) {
        TetrisPiece p = *nextPiece; // make a copy
        p.rotateLeft();
        mask = p.getMask();
        width = p.getWidth();
        c = p.getColor();
    }
    
    for (int x = 0; x < 4; x++) {
        for (int y = 0; y < 4; y++) {
            int pos = x+(y*width);
            if (pos < mask.size() && mask[pos] != ' ') {
                drawPoint(x+11, y+2, ' ', c);
            } else {
                drawPoint(x+11, y+2, ' ', Color(0,0,0));
            }
        }
    }
}

void TerminalTetrisDisplay::drawScore(int score) {
    m_curses.print(25,21,"Score : " + std::to_string(score));
}

void TerminalTetrisDisplay::drawLevel(int level) {
    m_curses.print(25,20,"Level : " + std::to_string(level) + "     ");
}

void TerminalTetrisDisplay::drawRemainingLines(int remainingLines) {
    m_curses.print(25, 19, "Lines Remaining : " + std::to_string(remainingLines) + "     ");
}

void TerminalTetrisDisplay::flush() {
    m_curses.flush();
}

void TerminalTetrisDisplay::drawPoint(int x, int y, char ch, const Color& color) {
    m_curses.draw(x*2 + m_xOffset,y + m_yOffset,ch,color);
    m_curses.draw(x*2+1 + m_xOffset,y + m_yOffset,ch,color);
}
