//
//  SDLUtil.h
//  TetraTable
//
//  Created by Ben La Monica on 3/23/15.
//  Copyright (c) 2015 Benjamin Alan La Monica. All rights reserved.
//

#ifndef __TetraTable__SDLUtil__
#define __TetraTable__SDLUtil__

#include <stdio.h>
#include <memory>
#include <SDL2/SDL.h>

struct SDLEvent {
    typedef std::shared_ptr<SDLEvent> Ptr;
    SDL_Joystick *joy;
    SDL_Event m_event;
};


class SDLUtil {
public:
    static SDLUtil& instance();
    virtual ~SDLUtil();
    SDLEvent::Ptr getNextEvent();
private:
    SDL_Joystick *m_joy;
    SDLUtil();
    SDLUtil( const SDLUtil& other ) = delete; // non construction-copyable
    SDLUtil& operator=( const SDLUtil& ) = delete; // non copyable

};

#endif /* defined(__TetraTable__SDLUtil__) */
