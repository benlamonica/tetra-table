//
//  Curses.h
//  TetraTable
//
//  Created by Ben La Monica on 1/5/15.
//  Copyright (c) 2015 Benjamin Alan La Monica. All rights reserved.
//

#ifndef __TetraTable__Curses__
#define __TetraTable__Curses__

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
    void redraw();

private:
    std::mutex m_keyboardMutex;
    std::mutex m_screenMutex;
    ColorMap m_colorMap;
    short m_colorIdx;
};

#endif /* defined(__TetraTable__Curses__) */
