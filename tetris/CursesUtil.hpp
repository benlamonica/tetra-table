//
//  Curses.h
//  tetris
//
//  Created by Ben La Monica on 1/5/15.
//  Copyright (c) 2015 Benjamin Alan La Monica. All rights reserved.
//

#ifndef __tetris__Curses__
#define __tetris__Curses__

#include <stdio.h>
#include <mutex>

class CursesUtil {
public:
    static CursesUtil& instance();
private:
    CursesUtil();
    CursesUtil( const CursesUtil& other ) = delete; // non construction-copyable
    CursesUtil& operator=( const CursesUtil& ) = delete; // non copyable

public:
    virtual ~CursesUtil();
    int getChar();

private:
    std::mutex m_keyboardMutex;
    std::mutex m_screenMutex;
};

#endif /* defined(__tetris__Curses__) */
