//
//  SDLJoystickInput.cpp
//  TetraTable
//
//  Created by Ben La Monica on 3/23/15.
//  Copyright (c) 2015 Benjamin Alan La Monica. All rights reserved.
//

#include "SDLJoystickInput.hpp"
#include "../util/SDLUtil.hpp"
#include <syslog.h>
#include <SDL2/SDL.h>
#include "../util/TimeUtil.hpp"

SDLJoystickInput::SDLJoystickInput(TetraTable *game, TetraTableInput::Ptr delegate) : TetraTableInput(game, delegate), m_direction(pieces::NONE){
    
}

SDLJoystickInput::~SDLJoystickInput() {
    
}

void SDLJoystickInput::getNextMove(std::vector<pieces::Move>& moves) {
    SDLUtil& sdl = SDLUtil::instance();
    using namespace pieces;
    using namespace util;
    SDLEvent::Ptr event = sdl.getNextEvent();
    if (event && event->m_event.type >= 0x600 && event->m_event.type < 0x700) {
        switch(event->m_event.type) {
            case SDL_JOYAXISMOTION: {
                Sint16 x = SDL_JoystickGetAxis(event->joy,0);
                Sint16 y = SDL_JoystickGetAxis(event->joy,1);
                syslog(LOG_WARNING, "axis event: x,y (%d,%d)", x, y);
                if (x < 128) {
                    m_direction.store(LEFT);
                    m_repeatingStarts.store(now() + 200000000);
                    syslog(LOG_WARNING, "LEFT %lld (%lld)", m_repeatingStarts.load(), now());
                } else if (x > 128) {
                    m_direction.store(RIGHT);
                    m_repeatingStarts.store(now() + 200000000);
                    syslog(LOG_WARNING, "RIGHT");
                } else if (y > 128) {
                    syslog(LOG_WARNING, "DOWN");
                    m_repeatingStarts.store(now() + 200000000);
                    m_direction.store(DOWN);
                } else {
                    m_repeatingStarts.store(INT64_MAX);
                    m_direction.store(NONE);
                }
                break;
            }
            case SDL_JOYBUTTONDOWN: {
                Uint8 button = event->m_event.jbutton.button;
                syslog(LOG_WARNING, "button %d %s", button, event->m_event.jbutton.state == SDL_PRESSED ? "pressed" : "released");
                if (button == 0) {
                    moves.push_back(ROTATE_LEFT);
                } else if (button == 1) {
                    moves.push_back(DROP);
                } else if (button == 2) {
                    moves.push_back(HOLD_PIECE);
                } else if (button == 3) {
                    moves.push_back(ROTATE_RIGHT);
                } else if (button == 4) {
                    //moves.push_back(QUIT);
                }
                break;
            }
        }
        moves.push_back(m_direction.load());
    } else {
        if (m_repeatingStarts.load() <= util::now()) {
            moves.push_back(m_direction.load());
        }
        util::millisleep(30);
    }
}
