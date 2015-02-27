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
#include <map>

class Color;

class CursesUtil {
public:
    static CursesUtil& instance();
    typedef std::map<int,short> ColorMap;
private:
    CursesUtil();
    CursesUtil( const CursesUtil& other ) = delete; // non construction-copyable
    CursesUtil& operator=( const CursesUtil& ) = delete; // non copyable

public:
    virtual ~CursesUtil();
    int getChar();
    void draw(int x, int y, char ch, const Color &c);
    void print(int x, int y, const std::string &s);
    void flush();

private:
    std::mutex m_keyboardMutex;
    std::mutex m_screenMutex;
    ColorMap m_colorMap;
    short m_colorIdx;
};

#endif /* defined(__tetris__Curses__) */
