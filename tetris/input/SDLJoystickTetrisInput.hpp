//
//  SDLJoystickTetrisInput.h
//  tetris
//
//  Created by Ben La Monica on 3/23/15.
//  Copyright (c) 2015 Benjamin Alan La Monica. All rights reserved.
//

#ifndef __tetris__SDLJoystickTetrisInput__
#define __tetris__SDLJoystickTetrisInput__

#include <stdio.h>
#include "TetrisInput.hpp"

class SDLJoystickTetrisInput : public TetrisInput {

public:
    SDLJoystickTetrisInput(Tetris *game, TetrisInput::Ptr delegate);
    virtual ~SDLJoystickTetrisInput();
    virtual void getNextMove(std::vector<tetris::Move>& moves) override;
    
private:
    std::atomic<int64_t> m_repeatingStarts;
    std::atomic<tetris::Move> m_direction;

};

#endif /* defined(__tetris__SDLJoystickTetrisInput__) */
