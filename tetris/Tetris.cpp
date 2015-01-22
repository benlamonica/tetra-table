//
//  Tetris.cpp
//  tetris
//
//  Created by La Monica Family on 12/28/14.
//  Copyright (c) 2014 Benjamin Alan La Monica. All rights reserved.
//

#include "Tetris.hpp"
#include "TetrisDisplay.hpp"
#include <time.h>

Tetris::~Tetris() {
    
}

Tetris::Tetris(std::shared_ptr<TetrisDisplay> display) : m_display(display), m_isRunning(true) {
    
};

void Tetris::run() {
    while(m_isRunning.load()) {
        struct timespec sleepTime = {1,0};
        nanosleep(&sleepTime, NULL);
        m_display->drawBoard(m_board, m_currentPiece);
    }
}

void Tetris::moveLeft() {

}

void Tetris::moveRight() {

}

void Tetris::moveDown() {

}

void Tetris::drop() {

}

void Tetris::rotate() {

}

void Tetris::quit() {
    m_isRunning.store(false);
}

