//
//  TetraTableInput.cpp
//  TetraTable
//
//  Created by La Monica Family on 12/28/14.
//  Copyright (c) 2014 Benjamin Alan La Monica. All rights reserved.
//

#include <stdio.h>
#include <syslog.h>
#include "TetraTableInput.hpp"

TetraTableInput::~TetraTableInput() {
    m_isRunning.store(false);
    if (m_inputThread && m_inputThread->joinable()) {
        m_inputThread->join();
    }
}

TetraTableInput::TetraTableInput(TetraTable *game, TetraTableInput::Ptr delegate) : m_game(game), m_isRunning(false), m_delegate(delegate)
{
    
}

void TetraTableInput::run() {
    if (!m_isRunning.exchange(true)) {
        m_inputThread = std::make_shared<std::thread>(&TetraTableInput::dispatchMoves, this);
    }
}

void TetraTableInput::stop() {
    m_isRunning.store(false);
}

void TetraTableInput::addMove(pieces::Move move) {
    if (m_delegate) {
        m_delegate->addMove(move);
    } else {
        std::lock_guard<std::mutex> lock(m_movesMutex);
        m_moves.push_back(move);
        syslog(LOG_WARNING, "addMove : %d", move);
    }
}

void TetraTableInput::dispatchMoves() {
    while (m_isRunning.load()) {
        std::lock_guard<std::mutex> lock(m_movesMutex);
        using namespace pieces;
        getNextMove(m_moves);
        if (!m_moves.empty()) {
            bool hasAutoDrop = false;
            for (MoveVec::const_iterator it = m_moves.begin(); it != m_moves.end(); ++it) {
                // if there is a delegate, delegate all of the moves to the other TetraTableInput
                if (m_delegate) {
                    m_delegate->addMove(*it);
                    continue;
                }
                switch(*it) {
                    case DOWN:
                        m_game->moveDown();
                        break;
                    case DOWN_AUTODROP:
                        m_game->moveDown(true);
                        hasAutoDrop = true;
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
            m_moves.clear();
            m_game->draw(hasAutoDrop);
        }
    }
}
