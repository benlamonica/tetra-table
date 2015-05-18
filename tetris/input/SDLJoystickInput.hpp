//
//  SDLJoystickInput.h
//  TetraTable
//
//  Created by Ben La Monica on 3/23/15.
//  Copyright (c) 2015 Benjamin Alan La Monica. All rights reserved.
//

#ifndef __TetraTable__SDLJoystickInput__
#define __TetraTable__SDLJoystickInput__

#include <stdio.h>
#include "TetraTableInput.hpp"

class SDLJoystickInput : public TetraTableInput {

public:
    SDLJoystickInput(TetraTable *game, TetraTableInput::Ptr delegate);
    virtual ~SDLJoystickInput();
    virtual void getNextMove(std::vector<pieces::Move>& moves) override;
    
private:
    std::atomic<int64_t> m_repeatingStarts;
    std::atomic<pieces::Move> m_direction;

};

#endif /* defined(__TetraTable__SDLJoystickInput__) */
