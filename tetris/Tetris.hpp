//
//  Tetris.h
//  tetris
//
//  Created by La Monica Family on 12/28/14.
//  Copyright (c) 2014 Benjamin Alan La Monica. All rights reserved.
//

#ifndef __tetris__Tetris__
#define __tetris__Tetris__

#include <stdio.h>
#include "TetrisPiece.hpp"
#include <deque>
#include <memory>
#include <random>
#include <chrono>

class TetrisDisplay;

class Tetris {
public:
    virtual ~Tetris();
    Tetris(std::shared_ptr<TetrisDisplay> display);
    void moveLeft();
    void moveRight();
    void moveDown();
    void drop(bool hard);
    void rotate();
    void run();
    void quit();
    
private:
    void draw();
    void lockPiece();
    bool collisionAt(TetrisPiece::Ptr piece, int pieceX, int pieceY);
    int calculateDropPosition();
    void fillPieceBag();
    void takeNextPiece();
    void checkForLock();
    std::deque<TetrisPiece::Ptr> m_pieces;
    std::shared_ptr<TetrisDisplay> m_display;
    std::atomic<bool> m_isRunning;
    std::vector<std::string> m_board;
    TetrisPiece::Ptr m_currentPiece;
    std::string m_currentMask;
    int m_shadowY;
    int m_boardHeight;
    int m_score;
    int m_boardWidth;
    long m_dropSpeed; // ms between each line dropped
    long m_lockSpeed;
    std::mt19937 m_shuffler;
    std::atomic<int64_t> m_lockTime;
    std::atomic<bool> m_aboutToLock;
    std::atomic<int64_t> m_dropTime;
};

#endif /* defined(__tetris__Tetris__) */
