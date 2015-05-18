//
//  SDLAudio.h
//  TetraTable
//
//  Created by Ben La Monica on 3/23/15.
//  Copyright (c) 2015 Benjamin Alan La Monica. All rights reserved.
//

#ifndef __TetraTable__SDLAudio__
#define __TetraTable__SDLAudio__

#include <stdio.h>
#include <SDL2_mixer/SDL_mixer.h>
#include "TetraTableAudio.hpp"

class SDLAudio : public TetraTableAudio {
public:
    SDLAudio();
    virtual ~SDLAudio();
    
    virtual void playMusic();
    virtual void stopMusic();
    virtual void playSound(Sounds sound);
private:
    Mix_Music *music;
    Mix_Chunk *sounds[10];

};

#endif /* defined(__TetraTable__SDLAudio__) */
