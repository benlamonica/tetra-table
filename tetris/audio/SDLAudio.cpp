//
//  SDLAudio.cpp
//  TetraTable
//
//  Created by Ben La Monica on 3/23/15.
//  Copyright (c) 2015 Benjamin Alan La Monica. All rights reserved.
//

#include "SDLAudio.hpp"
#include <SDL2_mixer/SDL_mixer.h>
#include <syslog.h>

SDLAudio::SDLAudio() {
    if (Mix_Init(MIX_INIT_MP3) != MIX_INIT_MP3) {
        syslog(LOG_WARNING, "Unable to init MP3 mixer: %s", Mix_GetError());
    }
    
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1) {
        syslog(LOG_WARNING, "Unable to open audio: %s", Mix_GetError());
    }

    music = Mix_LoadMUS("audio/music.mp3");
    
    sounds[0] = Mix_LoadWAV("audio/1.wav");
    sounds[1] = Mix_LoadWAV("audio/2.wav");
    sounds[2] = Mix_LoadWAV("audio/3.wav");
    sounds[3] = Mix_LoadWAV("audio/4.wav");
    sounds[4] = Mix_LoadWAV("audio/5.wav");
    sounds[5] = Mix_LoadWAV("audio/6.wav");
    sounds[6] = Mix_LoadWAV("audio/7.wav");
    sounds[7] = Mix_LoadWAV("audio/8.wav");
    sounds[8] = Mix_LoadWAV("audio/9.wav");
    sounds[9] = Mix_LoadWAV("audio/10.wav");
}

SDLAudio::~SDLAudio() {
    Mix_FreeMusic(music);
    for (int i = 0; i < 10; i++) {
        Mix_FreeChunk(sounds[i]);
    }
    Mix_Quit();
}

void SDLAudio::playMusic() {
    Mix_VolumeMusic(128/3);
    Mix_PlayMusic(music, -1);
}

void SDLAudio::stopMusic() {
    Mix_HaltMusic();
}

void SDLAudio::playSound(Sounds sound) {
    Mix_PlayChannel(-1, sounds[sound-1], 0);
}
