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
#include "audio/MacAudio.hpp"
#include "display/TerminalTetrisDisplay.hpp"


int main(int argc, const char * argv[]) {
    syslog(LOG_INFO, "starting tetris...");
    std::shared_ptr<TetrisAudio> audio = std::make_shared<MacAudio>();
    std::shared_ptr<TetrisDisplay> display = std::make_shared<TerminalTetrisDisplay>(20,20);
    Tetris game(display, audio);
    KeyboardTetrisInput input(&game);
    input.run();
    game.run();
    input.stop();
    return 0;
}








