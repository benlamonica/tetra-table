//
//  SDLUtil.cpp
//  TetraTable
//
//  Created by Ben La Monica on 3/23/15.
//  Copyright (c) 2015 Benjamin Alan La Monica. All rights reserved.
//

#include "SDLUtil.hpp"
#include <syslog.h>

SDLUtil::SDLUtil() {
    SDL_Init(SDL_INIT_GAMECONTROLLER | SDL_INIT_AUDIO);

    int numJoysticks = SDL_NumJoysticks();
    syslog(LOG_WARNING, "found %d joysticks", numJoysticks);
    for (int i = 0; i < numJoysticks; i++) {
        syslog(LOG_WARNING, "joystick %d = %s", i, SDL_JoystickNameForIndex(i));
        m_joy = SDL_JoystickOpen(i);
    }
}

SDLUtil::~SDLUtil() {
    SDL_JoystickClose(m_joy);
}

SDLEvent::Ptr SDLUtil::getNextEvent() {
    SDL_PumpEvents();
    SDLEvent::Ptr e = std::make_shared<SDLEvent>();
    e->joy = m_joy;
    if (SDL_PollEvent(&e->m_event)) {
        return e;
    }
    
    static SDLEvent::Ptr NO_EVENT;
    return NO_EVENT;
}

SDLUtil& SDLUtil::instance() {
    // c++11 garuntees that only one thread will be creating this
    static SDLUtil instance;
    return instance;
}