//
//  Tetris.cpp
//  tetris
//
//  Created by La Monica Family on 12/28/14.
//  Copyright (c) 2014 Benjamin Alan La Monica. All rights reserved.
//

#include "Tetris.hpp"
#include <time.h>

Tetris::~Tetris() {
    
}

Tetris::Tetris(std::shared_ptr<TetrisDisplay> display) : m_display(display), m_isRunning(true) {
    
};

void Tetris::run() {
    while(m_isRunning.load()) {
        struct timespec sleepTime = {1,0};
        nanosleep(&sleepTime, NULL);
    }
}

void Tetris::moveLeft() {
    printf("Move left.\n");
}

void Tetris::moveRight() {
    printf("Move right.\n");
}

void Tetris::moveDown() {
    printf("Move down.\n");
}

void Tetris::drop() {
    printf("drop.\n");
}

void Tetris::rotate() {
    printf("rotate\n");
}

void Tetris::quit() {
    m_isRunning.store(false);
}

