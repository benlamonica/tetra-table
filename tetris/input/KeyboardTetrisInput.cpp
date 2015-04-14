//
//  KeyboardTetrisInput.cpp
//  tetris
//
//  Created by La Monica Family on 1/2/15.
//  Copyright (c) 2015 Benjamin Alan La Monica. All rights reserved.
//

#include <curses.h>
#include <time.h>
#include "KeyboardTetrisInput.hpp"
#include "../util/CursesUtil.hpp"
#include "../pieces/TetrisMove.hpp"

KeyboardTetrisInput::KeyboardTetrisInput(Tetris *game) : m_curses(CursesUtil::instance()), super(game) {

}

KeyboardTetrisInput::~KeyboardTetrisInput() {
    
}

void KeyboardTetrisInput::getNextMove(std::vector<tetris::Move> &moves) {
    using namespace tetris;
    int ch = m_curses.getChar();
    if (ch != -1) {
        switch(ch) {
            case KEY_LEFT:
                moves.push_back(LEFT);
                break;
            case KEY_RIGHT:
                moves.push_back(RIGHT);
                break;
            case KEY_DOWN:
                moves.push_back(DOWN);
                break;
            case KEY_UP:
                moves.push_back(HOLD_PIECE);
                break;
            case ((int)'z'):
            case ((int)'Z'):
                moves.push_back(ROTATE_LEFT);
                break;
            case ((int)'x'):
            case ((int)'X'):
                moves.push_back(ROTATE_RIGHT);
                break;
            case ((int)' '):
                moves.push_back(DROP);
                break;
            case ((int) 'q'):
            case ((int) 'Q'):
                moves.push_back(QUIT);
                break;
        }
    } else {
        // sleep for 50 ms
        struct timespec sleepTime = {0,50000000};
        nanosleep(&sleepTime, NULL);
    }
}
