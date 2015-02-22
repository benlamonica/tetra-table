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
Tetris::~Tetris() {
    
}

Tetris::Tetris(std::shared_ptr<TetrisDisplay> display) : m_display(display), m_isRunning(true), m_boardHeight(20), m_boardWidth(10), m_dropSpeed(2000), m_shuffler(std::random_device()()) {
    for (int x = 0; x < m_boardWidth; x++) {
        for (int y = 0; y < m_boardHeight; y++) {
            m_board[x][y] = ' ';
        }
    }
    
    takeNextPiece();
};

void Tetris::takeNextPiece() {
    fillPieceBag();
    m_currentPiece = *m_pieces.begin();
    m_pieces.pop_front();
    m_currentPiece->setLocation(4, 0);
    strcpy(m_currentMask, "      ");
    m_currentPiece->getMask(m_currentMask);
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
        long sleep_time = m_dropSpeed * 1000000;
        struct timespec sleepTime = {sleep_time / 1000000000,sleep_time % 1000000000};
        nanosleep(&sleepTime, NULL);
        moveDown();
    }
}

void Tetris::draw() {
    m_display->drawBoard(m_board, m_currentPiece, m_shadowY);
}

void Tetris::cement() {
    int height = m_currentPiece->getHeight();
    int width = m_currentPiece->getWidth();
    
    // check to see if our piece will hit another piece
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            if (m_currentMask[x+(y*width)] != ' ') {
                m_board[m_currentPiece->getX() + x][m_currentPiece->getY() + y] = m_currentPiece->getRep();
            }
        }
    }
    takeNextPiece();
}

void Tetris::moveLeft() {
    if (m_currentPiece->getX() > 0 && !collisionAt(m_currentPiece, m_currentPiece->getX()-1, m_currentPiece->getY())) {
        m_currentPiece->moveLeft();
        m_shadowY = calculateDropPosition();
        draw();
    }
}

void Tetris::moveRight() {
    if (((m_currentPiece->getX() + m_currentPiece->getWidth()) < m_boardWidth) && !collisionAt(m_currentPiece, m_currentPiece->getX()+1, m_currentPiece->getY())) {
        m_currentPiece->moveRight();
        m_shadowY = calculateDropPosition();
        draw();
    }
}

void Tetris::moveDown() {
    m_currentPiece->moveDown();
    if (m_currentPiece->getY() >= m_shadowY) {
        drop();
    }
    draw();
}

void Tetris::drop() {
    while (m_currentPiece->getY() < m_shadowY) {
        m_currentPiece->moveDown();
    }
    cement();
    draw();
}

void Tetris::rotate() {
    m_currentPiece->rotateRight();
    strcpy(m_currentMask, "      ");
    m_currentPiece->getMask(m_currentMask);
    m_shadowY = calculateDropPosition();
    draw();
}

void Tetris::quit() {
    m_isRunning.store(false);
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
            if (m_board[pieceX + x][pieceY + y] != ' ' && (m_currentMask[x+(y*width)] != ' ')) {
                // found a collision
                return true;
            }
        }
    }

    return false;
}

// calculates where on the y axis the shadow should start
int Tetris::calculateDropPosition() {
    int shadowY = 0; // start at the top
    while (!collisionAt(m_currentPiece, m_currentPiece->getX(), shadowY)) {
        shadowY++; // haven't found a collision yet, move the check down a line
    }
    return shadowY - 1;
}
