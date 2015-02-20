//
//  TerminalTetrisDisplay.cpp
//  tetris
//
//  Created by Ben La Monica on 2/17/15.
//  Copyright (c) 2015 Benjamin Alan La Monica. All rights reserved.
//

#include "TerminalTetrisDisplay.hpp"
#include "CursesUtil.hpp"

TerminalTetrisDisplay::TerminalTetrisDisplay() : m_curses(CursesUtil::instance()) {

}

TerminalTetrisDisplay::~TerminalTetrisDisplay() {
    
}

void TerminalTetrisDisplay::drawPoint(int x, int y, char ch, const Color& color) {
    m_curses.draw(x*2,y,ch,color);
    m_curses.draw(x*2+1,y,ch,color);
}
