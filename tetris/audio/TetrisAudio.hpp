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
        ROTATE,
        SOFT_DROP,
        HARD_DROP,
        LOCK,
        REMOVE_LINE,
        NEW_PIECE,
        TETRIS,
        LEVEL_UP,
        PIECE_FREEZE,
        GAME_OVER
    };
    
    virtual void playMusic() = 0;
    virtual void playSound(Sounds sound) = 0;
    virtual ~TetrisAudio();
protected:
    TetrisAudio();
};


#endif /* defined(__tetris__TetrisAudio__) */
