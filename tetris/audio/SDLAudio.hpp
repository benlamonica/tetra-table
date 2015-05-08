//
//  SDLAudio.h
//  tetris
//
//  Created by Ben La Monica on 3/23/15.
//  Copyright (c) 2015 Benjamin Alan La Monica. All rights reserved.
//

#ifndef __tetris__SDLAudio__
#define __tetris__SDLAudio__

#include <stdio.h>
#include "TetrisAudio.hpp"

class SDLAudio : public TetrisAudio {
public:
    SDLAudio();
    virtual ~SDLAudio();
    
    virtual void playMusic();
    virtual void stopMusic();
    virtual void playSound(Sounds sound);
};

#endif /* defined(__tetris__SDLAudio__) */
