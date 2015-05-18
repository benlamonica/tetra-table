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
#include <memory>
#include "../Tetris.hpp"
#include "../pieces/TetrisMove.hpp"

class TetrisInput {
public:
    typedef std::shared_ptr<TetrisInput> Ptr;
    
    TetrisInput(Tetris *game, TetrisInput::Ptr delegate);
    void run();
    void stop();
    virtual ~TetrisInput();
    void addMove(tetris::Move move);
protected:
    virtual void getNextMove(std::vector<tetris::Move> &moves) = 0;
private:
    typedef std::vector<tetris::Move> MoveVec;
    MoveVec m_moves;
    void dispatchMoves();
    Tetris *m_game;
    std::atomic<bool> m_isRunning;
    std::shared_ptr<std::thread> m_inputThread;
    std::mutex m_movesMutex;
    TetrisInput::Ptr m_delegate;
};


#endif
