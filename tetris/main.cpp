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

int main(int argc, const char * argv[]) {
    putenv((char *)"TERM=xterm-256color");
    std::shared_ptr<TetrisDisplay> display;
    Tetris game(display);
    KeyboardTetrisInput input(&game);
    input.run();
    game.run();
    input.stop();
    return 0;
}








