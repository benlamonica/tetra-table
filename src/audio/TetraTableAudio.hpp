//
//  TetraTableAudio.h
//  TetraTable
//
//  Created by Ben La Monica on 3/4/15.
//  Copyright (c) 2015 Benjamin Alan La Monica. All rights reserved.
//

#ifndef __TetraTable__TetraTableAudio__
#define __TetraTable__TetraTableAudio__

#include <stdio.h>

class TetraTableAudio {
public:
    enum Sounds {
        MUSIC,
        ROTATE, // nuh
        SOFT_DROP, // shhh
        HARD_DROP, // tss
        LOCK, // click
        REMOVE_LINE, // bloop
        NEW_PIECE, // boop
        FOUR_LINES, // ba-la-la-la-la
        LEVEL_UP, // ba-doop ^
        PIECE_FREEZE, // tsh
        GAME_OVER // wah-wah
    };
    
    virtual void playMusic() = 0;
    virtual void stopMusic() = 0;
    virtual void playSound(Sounds sound) = 0;
    virtual ~TetraTableAudio();
protected:
    TetraTableAudio();
};


#endif /* defined(__TetraTable__TetraTableAudio__) */
