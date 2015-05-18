//
//  main.cpp
//  TetraTable
//
//  Created by La Monica Family on 12/26/14.
//  Copyright (c) 2014 Benjamin Alan La Monica. All rights reserved.
//

#include <iostream>
#include <stdlib.h>
#include <syslog.h>
#include "TetraTable.hpp"
#include "input/KeyboardInput.hpp"
#include "input/SDLJoystickInput.hpp"
#include "audio/SDLAudio.hpp"
#include "util/SDLUtil.hpp"
#include "display/TerminalDisplay.hpp"


int main(int argc, const char * argv[]) {
    syslog(LOG_INFO, "starting");
    SDLUtil::instance();
    std::shared_ptr<TetraTableAudio> audio = std::make_shared<SDLAudio>();
    std::shared_ptr<TetraTableDisplay> display = std::make_shared<TerminalDisplay>(20,20);
    TetraTable game(display, audio);
    std::shared_ptr<TetraTableInput> input;
    std::shared_ptr<SDLJoystickInput> joystick = std::make_shared<SDLJoystickInput>(&game, input);
    std::shared_ptr<KeyboardInput> keyboard = std::make_shared<KeyboardInput>(&game, joystick);
    game.setInputHandler(joystick);
    joystick->run();
    keyboard->run();
    game.run();
    keyboard->stop();
    joystick->stop();
    return 0;
}








