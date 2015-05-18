//
//  NoSoundAudio.h
//  TetraTable
//
//  Created by Ben La Monica on 3/4/15.
//  Copyright (c) 2015 Benjamin Alan La Monica. All rights reserved.
//

#ifndef __TetraTable__NoSoundAudio__
#define __TetraTable__NoSoundAudio__

#include <stdio.h>
#include "TetraTableAudio.hpp"


class NoSoundAudio : public TetraTableAudio {
public:
    virtual void playMusic();
    virtual void stopMusic();
    virtual void playSound(Sounds sound);
    NoSoundAudio();
    virtual ~NoSoundAudio();
};

#endif /* defined(__TetraTable__NoSoundAudio__) */
