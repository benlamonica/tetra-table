//
//  TetrisInput.cpp
//  tetris
//
//  Created by La Monica Family on 12/28/14.
//  Copyright (c) 2014 Benjamin Alan La Monica. All rights reserved.
//

#include <stdio.h>
#include "TetrisInput.hpp"

TetrisInput::~TetrisInput() {
    m_isRunning.store(false);
    if (m_inputThread.joinable()) {
        m_inputThread.join();
    }
}

void TetrisInput::dispatchMoves() {
    while (m_isRunning.load()) {
        TetrisInput::Move move = getNextMove();
        switch(move) {
            case DOWN:
                m_game->moveDown();
                break;
            case LEFT:
                m_game->moveLeft();
                break;
            case RIGHT:
                m_game->moveRight();
                break;
            case DROP:
                m_game->drop();
                break;
            case ROTATE:
                m_game->rotate();
                break;
        }
    }
}
