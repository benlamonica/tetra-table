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
#include "J.hpp"
#include "L.hpp"
#include "I.hpp"
#include "O.hpp"
#include "S.hpp"
#include "T.hpp"
#include "Z.hpp"
#include <utility>
#include <syslog.h>

CursesUtil::CursesUtil() : m_colorIdx(0) {
    initscr();
    start_color();
    cbreak();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    curs_set(0);
    
    // since xterm-256color doesn't actually support remapping of colors, just map the ones closest to what we want
    m_colorMap.insert(std::make_pair(0,0));
    init_pair(0,0,0);
    m_colorMap.insert(std::make_pair(J().getColor().key(), 20));
    init_pair(20,20,20);
    m_colorMap.insert(std::make_pair(L().getColor().key(), 208));
    init_pair(208,208,208);
    m_colorMap.insert(std::make_pair(I().getColor().key(), 14));
    init_pair(14,14,14);
    m_colorMap.insert(std::make_pair(O().getColor().key(), 228));
    init_pair(228,228,228);
    m_colorMap.insert(std::make_pair(S().getColor().key(), 83));
    init_pair(83,83,83);
    m_colorMap.insert(std::make_pair(T().getColor().key(), 93));
    init_pair(93,93,93);
    m_colorMap.insert(std::make_pair(Z().getColor().key(), 9));
    init_pair(9,9,9);
    m_colorMap.insert(std::make_pair(Color(5,5,5).key(), 236));
    init_pair(236,236,236);
    init_pair(13,13,13); // the unmapped color
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
        colorIdx = 13; // no mapping, make it pink so that it stands out
    } else {
        colorIdx = it->second;
    }
    attron(COLOR_PAIR(colorIdx));
    mvaddch(y, x, ' ');//(char)0x2588
    attroff(COLOR_PAIR(colorIdx));
}


CursesUtil& CursesUtil::instance() {
    // c++11 garuntees that only one thread will be creating this
    static CursesUtil instance;
    return instance;
}