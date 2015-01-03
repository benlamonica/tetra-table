//
//  TetrisInput.hpp
//  tetris
//
//  Created by La Monica Family on 12/28/14.
//  Copyright (c) 2014 Benjamin Alan La Monica. All rights reserved.
//

#ifndef tetris_TetrisInput_hpp
#define tetris_TetrisInput_hpp

#include <thread>
#include <atomic>
#include "Tetris.hpp"

class TetrisInput {
public:
    enum Move {
        LEFT,
        RIGHT,
        DOWN,
        DROP,
        ROTATE
    };
    
    TetrisInput(Tetris *game) : m_game(game), m_isRunning(true), m_inputThread(&TetrisInput::dispatchMoves, this) { }
    
    virtual ~TetrisInput();
protected:
    virtual Move getNextMove() = 0;
private:
    void dispatchMoves();
    Tetris *m_game;
    std::atomic<bool> m_isRunning;
    std::thread m_inputThread;
};


#endif
