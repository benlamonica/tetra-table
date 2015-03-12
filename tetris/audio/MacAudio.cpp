//
//  MacAudio.cpp
//  tetris
//
//  Created by Ben La Monica on 3/9/15.
//  Copyright (c) 2015 Benjamin Alan La Monica. All rights reserved.
//

#include "MacAudio.hpp"

MacAudio::MacAudio() {
    m_avPlayers = [NSMutableArray new];
}


MacAudio::~MacAudio() {
    [m_avPlayers removeAllObjects];
    m_avPlayers = nil;
}

void MacAudio::playMusic() {
    
}

void MacAudio::playSound(Sounds sound) {
    
}
