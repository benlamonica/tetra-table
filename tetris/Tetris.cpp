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
#include <algorithm>
#include <random>
#include <chrono>
#include "pieces/J.hpp"
#include "pieces/L.hpp"
#include "pieces/I.hpp"
#include "pieces/O.hpp"
#include "pieces/S.hpp"
#include "pieces/T.hpp"
#include "pieces/Z.hpp"
#include <syslog.h>

Tetris::~Tetris() {
    
}

Tetris::Tetris(std::shared_ptr<TetrisDisplay> display) : m_display(display), m_isRunning(true), m_boardHeight(20), m_boardWidth(10), m_dropSpeed(2000 * 1000000), m_lockSpeed(1000 * 1000000), m_shuffler(std::random_device()()), m_dropTime(m_dropSpeed * 1000000), m_lockTime(INT64_MAX), m_aboutToLock(false) {
    
    m_board.clear();
    for (int i = 0; i < m_boardWidth; i++) {
        m_board.push_back(std::string(m_boardHeight, ' '));
    }
    
    takeNextPiece();
};

namespace {
    int64_t now() {
        using namespace std::chrono;
        return duration_cast<nanoseconds>(high_resolution_clock::now().time_since_epoch()).count();
    }
}

void Tetris::takeNextPiece() {
    fillPieceBag();
    m_dropTime.store(now() + m_dropSpeed);
    m_lockTime.store(INT64_MAX);
    m_aboutToLock.store(false);
    m_currentPiece = *m_pieces.begin();
    m_pieces.pop_front();
    m_currentPiece->setLocation(4, 0);
    m_currentMask = m_currentPiece->getMask();
    m_shadowY = calculateDropPosition();
    draw();
}

void Tetris::fillPieceBag() {
    if (m_pieces.empty()) {
        m_pieces.push_back(std::make_shared<J>());
        m_pieces.push_back(std::make_shared<L>());
        m_pieces.push_back(std::make_shared<I>());
        m_pieces.push_back(std::make_shared<O>());
        m_pieces.push_back(std::make_shared<S>());
        m_pieces.push_back(std::make_shared<T>());
        m_pieces.push_back(std::make_shared<Z>());
        
        std::shuffle(m_pieces.begin(), m_pieces.end(), m_shuffler);
    }
}

void Tetris::run() {
    while(m_isRunning.load()) {
        int64_t nowInNs = now();
        int64_t lockInNs = m_lockTime.load();
        int64_t dropInNs = m_dropTime.load();
        if (lockInNs <= nowInNs || (dropInNs <= nowInNs && m_aboutToLock.load())) {
            lockPiece();
        } else if (dropInNs <= nowInNs) {
            moveDown();
        } else {
            int64_t timeToSleep = std::min(std::min(lockInNs,dropInNs) - nowInNs, (int64_t)m_lockSpeed);
            struct timespec sleepTime = {(timeToSleep / 1000000000), timeToSleep % 1000000000};
            // sleep until it's time to check the lock
            nanosleep(&sleepTime, NULL);
            continue;
        }
    }
}

void Tetris::draw() {
    m_display->drawBoard(m_board, m_currentPiece, m_shadowY);
}

void Tetris::lockPiece() {
    m_lockTime.store(INT64_MAX);
    m_aboutToLock.store(false);
    int height = m_currentPiece->getHeight();
    int width = m_currentPiece->getWidth();
    
    // check to see if our piece will hit another piece
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            if (m_currentMask[x+(y*m_currentPiece->getWidth())] != ' ') {
                m_board[m_currentPiece->getX() + x][m_currentPiece->getY() + y] = m_currentPiece->getRep();
            }
        }
    }
    takeNextPiece();
}

void Tetris::checkForLock() {
    if (m_currentPiece->getY() < m_shadowY) {
        m_aboutToLock.store(false);
        m_lockTime.store(INT64_MAX);
    } else {
        m_aboutToLock.store(true);
        m_lockTime.store(now() + m_lockSpeed);
    }
}

void Tetris::moveLeft() {
    if (m_currentPiece->getX() > 0 && !collisionAt(m_currentPiece, m_currentPiece->getX()-1, m_currentPiece->getY())) {
        m_currentPiece->moveLeft();
        m_shadowY = calculateDropPosition();
        checkForLock();
        draw();
    }
}

void Tetris::moveRight() {
    if (((m_currentPiece->getX() + m_currentPiece->getWidth()) < m_boardWidth) && !collisionAt(m_currentPiece, m_currentPiece->getX()+1, m_currentPiece->getY())) {
        m_currentPiece->moveRight();
        m_shadowY = calculateDropPosition();
        checkForLock();
        draw();
    }
}

void Tetris::moveDown() {
    m_dropTime.store(now()+m_dropSpeed);
    if (m_currentPiece->getY() >= m_shadowY) {
        drop(true);
        return;
    }
    
    m_currentPiece->moveDown();

    if (m_currentPiece->getY() == m_shadowY) {
        checkForLock();
    }
    draw();
}

void Tetris::drop(bool hard) {
    while (m_currentPiece->getY() < m_shadowY) {
        m_currentPiece->moveDown();
    }
    if(hard) {
        lockPiece();
    } else {
        checkForLock();
    }
    draw();
}

void Tetris::rotate() {
    m_currentPiece->rotateRight();
    m_currentMask = m_currentPiece->getMask();
    m_shadowY = calculateDropPosition();
    draw();
}

void Tetris::quit() {
    m_isRunning.store(false);
    exit(1);
}

// check to see if we have a collision at a given spot
bool Tetris::collisionAt(TetrisPiece::Ptr piece, int pieceX, int pieceY) {
    int height = piece->getHeight();
    int width = piece->getWidth();
    
    // check to see if our piece is at the bottom of the board
    if ((height + pieceY) > m_boardHeight) {
        return true;
    }
    
    // check to see if our piece will hit another piece
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            syslog(LOG_WARNING, "m_board[%d][%d] != '%c' %d", pieceX+x, pieceY+y, m_board[pieceX+x][pieceY+y], m_board[pieceX+x][pieceY+y] != ' ');
            syslog(LOG_WARNING, "m_currentMask[%d] != '%c' %d", x+(y*m_currentPiece->getWidth()), m_currentMask[x+(y*m_currentPiece->getWidth())], m_currentMask[x+(y*m_currentPiece->getWidth())] != ' ');
            if (m_board[pieceX + x][pieceY + y] != ' ' && (m_currentMask[x+(y*m_currentPiece->getWidth())] != ' ')) {
                // found a collision
                return true;
            }
        }
    }

    return false;
}

// calculates where on the y axis the shadow should start
int Tetris::calculateDropPosition() {
    int shadowY = m_currentPiece->getY(); // start at the piece and go down
    while (!collisionAt(m_currentPiece, m_currentPiece->getX(), shadowY)) {
        shadowY++; // haven't found a collision yet, move the check down a line
    }
    
    syslog(LOG_WARNING, "drop pos: %d", shadowY - 1);
    return shadowY - 1;
}
