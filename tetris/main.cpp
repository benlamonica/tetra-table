//
//  main.cpp
//  tetris
//
//  Created by La Monica Family on 12/26/14.
//  Copyright (c) 2014 Benjamin Alan La Monica. All rights reserved.
//

#include <iostream>
#include <stdlib.h>
#include <syslog.h>
#include "Tetris.hpp"
#include "input/KeyboardTetrisInput.hpp"
#include "input/SDLJoystickTetrisInput.hpp"
#include "audio/SDLAudio.hpp"
#include "util/SDLUtil.hpp"
#include "display/TerminalTetrisDisplay.hpp"


int main(int argc, const char * argv[]) {
    syslog(LOG_INFO, "starting");
    SDLUtil::instance();
    std::shared_ptr<TetrisAudio> audio = std::make_shared<SDLAudio>();
    std::shared_ptr<TetrisDisplay> display = std::make_shared<TerminalTetrisDisplay>(20,20);
    Tetris game(display, audio);
    KeyboardTetrisInput keyboard(&game);
    SDLJoystickTetrisInput joystick(&game);
    keyboard.run();
    joystick.run();
    game.run();
    keyboard.stop();
    joystick.stop();
    return 0;
}








