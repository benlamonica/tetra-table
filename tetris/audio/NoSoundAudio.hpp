//
//  NoSoundAudio.h
//  tetris
//
//  Created by Ben La Monica on 3/4/15.
//  Copyright (c) 2015 Benjamin Alan La Monica. All rights reserved.
//

#ifndef __tetris__NoSoundAudio__
#define __tetris__NoSoundAudio__

#include <stdio.h>
#include "TetrisAudio.hpp"


class NoSoundAudio : public TetrisAudio {
public:
    virtual void playMusic();
    virtual void stopMusic();
    virtual void playSound(Sounds sound);
    NoSoundAudio();
    virtual ~NoSoundAudio();
};

#endif /* defined(__tetris__NoSoundAudio__) */
