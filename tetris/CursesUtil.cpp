//
//  Curses.cpp
//  tetris
//
//  Created by Ben La Monica on 1/5/15.
//  Copyright (c) 2015 Benjamin Alan La Monica. All rights reserved.
//

#include "CursesUtil.hpp"
#include <curses.h>


CursesUtil::CursesUtil() {
    initscr();
    cbreak();
    keypad(stdscr, TRUE);
    nodelay(stdscr, true);
}

CursesUtil::~CursesUtil() {
    endwin();
}

int CursesUtil::getChar() {
    std::lock_guard<std::mutex> guard(m_keyboardMutex);
    return getch();
}

CursesUtil& CursesUtil::instance() {
    // c++11 garuntees that only one thread will be creating this
    static CursesUtil instance;
    return instance;
}