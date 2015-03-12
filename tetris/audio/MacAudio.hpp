//
//  MacAudio.h
//  tetris
//
//  Created by Ben La Monica on 3/9/15.
//  Copyright (c) 2015 Benjamin Alan La Monica. All rights reserved.
//

#ifndef __tetris__MacAudio__
#define __tetris__MacAudio__

#include <stdio.h>
#include "TetrisAudio.hpp"
#import <Foundation/Foundation.h>

class MacAudio : public TetrisAudio {
    public:
    MacAudio();
    virtual ~MacAudio();

    virtual void playMusic();
    virtual void playSound(Sounds sound);
private:
    NSMutableArray *m_avPlayers;
};



#endif /* defined(__tetris__MacAudio__) */
