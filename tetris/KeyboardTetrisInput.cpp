//
//  KeyboardTetrisInput.cpp
//  tetris
//
//  Created by La Monica Family on 1/2/15.
//  Copyright (c) 2015 Benjamin Alan La Monica. All rights reserved.
//

#include "KeyboardTetrisInput.hpp"
#include "CursesUtil.hpp"
#include <curses.h>
#include <time.h>

KeyboardTetrisInput::KeyboardTetrisInput(Tetris *game) : m_curses(CursesUtil::instance()), super(game) {

}

KeyboardTetrisInput::~KeyboardTetrisInput() {
    
}

TetrisInput::Move KeyboardTetrisInput::getNextMove() {
    int ch = m_curses.getChar();
    if (ch != -1) {
        switch(ch) {
            case KEY_LEFT:
                return LEFT;
            case KEY_RIGHT:
                return RIGHT;
            case KEY_DOWN:
                return DOWN;
            case KEY_UP:
                return ROTATE;
            case ((int)' '):
                return DROP;
            case ((int) 'q'):
            case ((int) 'Q'):
                return QUIT;
        }
    } else {
        // sleep for 50 ms
        struct timespec sleepTime = {0,50000000};
        nanosleep(&sleepTime, NULL);
    }
    
    return NONE;
}
