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

namespace {
    void addColor(CursesUtil::ColorMap &map, const Color &color, int colorIdx) {
        map.insert(std::make_pair(color.key(),colorIdx));
        init_pair(colorIdx,colorIdx,colorIdx);
    }
}

CursesUtil::CursesUtil() : m_colorIdx(0) {
    initscr();
    start_color();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    curs_set(0);
    
    // since xterm-256color doesn't actually support remapping of colors, just map the ones closest to what we want
    addColor(m_colorMap, Color(0,0,0), 0);
    addColor(m_colorMap, J().getColor(), 20);
    addColor(m_colorMap, L().getColor(), 208);
    addColor(m_colorMap, I().getColor(), 14);
    addColor(m_colorMap, O().getColor(), 228);
    addColor(m_colorMap, S().getColor(), 83);
    addColor(m_colorMap, T().getColor(), 93);
    addColor(m_colorMap, Z().getColor(), 9);
    addColor(m_colorMap, Color(5,5,5), 236);
    addColor(m_colorMap, Color(0x30,0x30,0x30), 244);

    addColor(m_colorMap, J().getGrayColor(), 237);
    addColor(m_colorMap, L().getGrayColor(), 239);
    addColor(m_colorMap, I().getGrayColor(), 241);
    addColor(m_colorMap, O().getGrayColor(), 243);
    addColor(m_colorMap, S().getGrayColor(), 245);
    addColor(m_colorMap, T().getGrayColor(), 247);
    addColor(m_colorMap, Z().getGrayColor(), 249);
    
    init_pair(13,13,13); // the unmapped color
}

CursesUtil::~CursesUtil() {
    endwin();
}

int CursesUtil::getChar() {
    std::lock_guard<std::mutex> guard(m_keyboardMutex);
    return getch();
}

void CursesUtil::flush() {
    std::lock_guard<std::mutex> guard(m_screenMutex);
    refresh();
}

void CursesUtil::print(int x, int y, const std::string &s) {
    move(y,x);
    printw(s.c_str());
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