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

class TetrisDisplay;

class Tetris {
public:
    virtual ~Tetris();
    Tetris(std::shared_ptr<TetrisDisplay> display);
    void moveLeft();
    void moveRight();
    void moveDown();
    void drop();
    void rotate();
    void run();
    void quit();
    
private:
    void draw();
    void cement();
    bool collisionAt(TetrisPiece::Ptr piece, int pieceX, int pieceY);
    int calculateDropPosition();
    void fillPieceBag();
    void takeNextPiece();
    std::deque<TetrisPiece::Ptr> m_pieces;
    std::shared_ptr<TetrisDisplay> m_display;
    std::atomic<bool> m_isRunning;
    char m_board[10][20];
    TetrisPiece::Ptr m_currentPiece;
    char m_currentMask[7];
    int m_shadowY;
    int m_boardHeight;
    int m_score;
    int m_boardWidth;
    long m_dropSpeed; // ms between each line dropped
    std::mt19937 m_shuffler;
};

#endif /* defined(__tetris__Tetris__) */
