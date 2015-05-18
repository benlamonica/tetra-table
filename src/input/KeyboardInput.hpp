//
//  KeyboardInput.h
//  TetraTable
//
//  Created by La Monica Family on 1/2/15.
//  Copyright (c) 2015 Benjamin Alan La Monica. All rights reserved.
//

#ifndef __TetraTable__KeyboardInput__
#define __TetraTable__KeyboardInput__

#include <stdio.h>

#include "TetraTableInput.hpp"
#include "../util/CursesUtil.hpp"

class TetraTable;

class KeyboardInput : public TetraTableInput {
public:
    KeyboardInput(TetraTable *game, TetraTableInput::Ptr delegate);
    virtual ~KeyboardInput();
protected:
    virtual void getNextMove(std::vector<pieces::Move> &moves);
private:
    CursesUtil& m_curses;
    typedef TetraTableInput super;
};
#endif /* defined(__TetraTable__KeyboardInput__) */
