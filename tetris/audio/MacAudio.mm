//
//  MacAudio.cpp
//  tetris
//
//  Created by Ben La Monica on 3/9/15.
//  Copyright (c) 2015 Benjamin Alan La Monica. All rights reserved.
//

#include "MacAudio.hpp"

MacAudio::MacAudio() {
    m_avPlayers = [NSMutableDictionary new];
}


MacAudio::~MacAudio() {
    [m_avPlayers removeAllObjects];
    m_avPlayers = nil;
}

void MacAudio::playMusic() {
    NSURL *musicUrl = [[NSURL alloc] initWithString:@"file:///Users/ben/Documents/code/tetra-table/tetris/audio/music.mp3"];
    NSError *err;
    AVAudioPlayer *player = [[AVAudioPlayer alloc] initWithContentsOfURL:musicUrl fileTypeHint:@"mp3" error:&err];
    if (err != nil) {
        NSLog(@"%@", err);
    } else {
        [player prepareToPlay];
        [player setVolume:0.1];
        [player setNumberOfLoops:-1];
        [player play];
        m_avPlayers[[NSNumber numberWithInt:TetrisAudio::MUSIC]] = player;
    }
}

void MacAudio::stopMusic() {
    AVAudioPlayer *player = getAvailablePlayer(TetrisAudio::MUSIC);
    [player stop];
}


AVAudioPlayer* MacAudio::getAvailablePlayer(Sounds sound) {
    AVAudioPlayer *player = [m_avPlayers objectForKey:[NSNumber numberWithInt:sound]];
    if (player == nil) {
        NSURL *url = [[NSURL alloc] initWithString:[NSString stringWithFormat:@"file:///Users/ben/Documents/code/tetra-table/tetris/audio/%d.mp3", sound]];
        NSError *err;
        player = [[AVAudioPlayer alloc] initWithContentsOfURL:url fileTypeHint: @"mp3" error:&err];
        
        if (err != nil) {
            NSLog(@"%@", err);
        } else {
            [player prepareToPlay];
            m_avPlayers[[NSNumber numberWithInt:sound]] = player;
        }
    }
    
    [player stop];
    [player setCurrentTime:0];
    return player;
}

void MacAudio::playSound(Sounds sound) {
    AVAudioPlayer *player = getAvailablePlayer(sound);
    [player play];
}
