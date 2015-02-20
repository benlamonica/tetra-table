//
//  main.cpp
//  tetris
//
//  Created by La Monica Family on 12/26/14.
//  Copyright (c) 2014 Benjamin Alan La Monica. All rights reserved.
//

#include <iostream>
#include <stdlib.h>
#include "Tetris.hpp"
#include "KeyboardTetrisInput.hpp"
#include "TerminalTetrisDisplay.hpp"
#include <syslog.h>


int main(int argc, const char * argv[]) {
//    fclose(stderr);
//    putenv((char *)"TERM=xterm-256color");
    syslog(LOG_INFO, "starting tetris...");
    std::shared_ptr<TetrisDisplay> display = std::make_shared<TerminalTetrisDisplay>();;
    Tetris game(display);
    KeyboardTetrisInput input(&game);
    input.run();
    game.run();
    input.stop();
    return 0;
}








