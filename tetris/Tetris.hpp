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
    bool isCollision(int x, int y);
    std::shared_ptr<TetrisDisplay> m_display;
    std::atomic<bool> m_isRunning;
    char m_board[10][20];
    int m_x;
    int m_y;
    TetrisPiece::Ptr m_currentPiece;
};

#endif /* defined(__tetris__Tetris__) */
