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
    if (m_inputThread && m_inputThread->joinable()) {
        m_inputThread->join();
    }
}

TetrisInput::TetrisInput(Tetris *game) : m_game(game), m_isRunning(false)
{
}

void TetrisInput::run() {
    if (!m_isRunning.exchange(true)) {
        m_inputThread = std::make_shared<std::thread>(&TetrisInput::dispatchMoves, this);
    }
}

void TetrisInput::stop() {
    m_isRunning.store(false);
}

void TetrisInput::dispatchMoves() {

    typedef std::vector<tetris::Move> MoveVec;
    MoveVec moves;
    while (m_isRunning.load()) {
        using namespace tetris;
        moves.clear();
        getNextMove(moves);
        for (MoveVec::const_iterator it = moves.begin(); it != moves.end(); ++it) {
            switch(*it) {
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
                    m_game->drop(true);
                    break;
                case ROTATE_LEFT:
                case ROTATE_RIGHT:
                    m_game->rotate(*it);
                    break;
                case HOLD_PIECE:
                    m_game->holdPiece();
                    break;
                case QUIT:
                    m_game->quit();
                default:
                    break;
            }
        }
    }
}
