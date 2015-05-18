//
//  TetraTableInput.hpp
//  TetraTable
//
//  Created by La Monica Family on 12/28/14.
//  Copyright (c) 2014 Benjamin Alan La Monica. All rights reserved.
//

#ifndef TetraTable_TetraTableInput_hpp
#define TetraTable_TetraTableInput_hpp

#include <thread>
#include <atomic>
#include <memory>
#include "../TetraTable.hpp"
#include "../pieces/TetraTableMove.hpp"

class TetraTableInput {
public:
    typedef std::shared_ptr<TetraTableInput> Ptr;
    
    TetraTableInput(TetraTable *game, TetraTableInput::Ptr delegate);
    void run();
    void stop();
    virtual ~TetraTableInput();
    void addMove(pieces::Move move);
protected:
    virtual void getNextMove(std::vector<pieces::Move> &moves) = 0;
private:
    typedef std::vector<pieces::Move> MoveVec;
    MoveVec m_moves;
    void dispatchMoves();
    TetraTable *m_game;
    std::atomic<bool> m_isRunning;
    std::shared_ptr<std::thread> m_inputThread;
    std::mutex m_movesMutex;
    TetraTableInput::Ptr m_delegate;
};


#endif
