//
//  Curses.cpp
//  tetris
//
//  Created by Ben La Monica on 1/5/15.
//  Copyright (c) 2015 Benjamin Alan La Monica. All rights reserved.
//

#define _XOPEN_SOURCE_EXTENDED 1

#include "CursesUtil.hpp"
#include <curses.h>
#include "TetrisPiece.hpp"
#include <utility>
#include <syslog.h>

CursesUtil::CursesUtil() : m_colorIdx(0) {
    initscr();
    start_color();
    cbreak();
    keypad(stdscr, TRUE);
    nodelay(stdscr, true);
    curs_set(0);
}

CursesUtil::~CursesUtil() {
    endwin();
}

int CursesUtil::getChar() {
    std::lock_guard<std::mutex> guard(m_keyboardMutex);
    return getch();
}

void CursesUtil::draw(int x, int y, char ch, const Color &c) {
    std::lock_guard<std::mutex> guard(m_screenMutex);
    ColorMap::iterator it = m_colorMap.find(c.key());
    short colorIdx = m_colorIdx;
    if (it == m_colorMap.end()) {
        syslog(LOG_WARNING, "adding color[%d] %x to color map", colorIdx, c.key());
        init_color(colorIdx, c.r, c.g, c.b);
        init_pair(colorIdx, colorIdx, COLOR_BLACK);
        m_colorIdx++;
        m_colorMap.insert(std::make_pair(c.key(), colorIdx));
    } else {
        colorIdx = it->second;
    }
    COLOR_PAIR(colorIdx);
    mvaddch(y, x, ch);//(char)0x2588
}


CursesUtil& CursesUtil::instance() {
    // c++11 garuntees that only one thread will be creating this
    static CursesUtil instance;
    return instance;
}