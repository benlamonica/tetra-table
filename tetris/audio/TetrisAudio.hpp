//
//  TetrisAudio.h
//  tetris
//
//  Created by Ben La Monica on 3/4/15.
//  Copyright (c) 2015 Benjamin Alan La Monica. All rights reserved.
//

#ifndef __tetris__TetrisAudio__
#define __tetris__TetrisAudio__

#include <stdio.h>

class TetrisAudio {
public:
    enum Sounds {
        MUSIC,
        ROTATE, // nuh
        SOFT_DROP, // shhh
        HARD_DROP, // tss
        LOCK, // click
        REMOVE_LINE, // bloop
        NEW_PIECE, // boop
        TETRIS, // ba-la-la-la-la
        LEVEL_UP, // ba-doop ^
        PIECE_FREEZE, // tsh
        GAME_OVER // wah-wah
    };
    
    virtual void playMusic() = 0;
    virtual void stopMusic() = 0;
    virtual void playSound(Sounds sound) = 0;
    virtual ~TetrisAudio();
protected:
    TetrisAudio();
};


#endif /* defined(__tetris__TetrisAudio__) */
