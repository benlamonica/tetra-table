//
//  HyperionDispay.h
//  tetra-table
//
//  Created by Ben La Monica on 6/22/15.
//  Copyright (c) 2015 Benjamin Alan La Monica. All rights reserved.
//

#ifndef __tetra_table__HyperionDispay__
#define __tetra_table__HyperionDispay__

#include <stdio.h>
#include "TetraTableDisplay.hpp"

class HyperionDisplay : public TetraTableDisplay {
public:
    virtual void drawNextPiece(TetraTablePiece::Ptr nextPiece);
    virtual void drawHeldPiece(TetraTablePiece::Ptr heldPiece);
    virtual void drawScore(int score);
    virtual void drawLevel(int level);
    virtual void drawRemainingLines(int remainingLines);
    virtual void flush();
    virtual void redraw();
    HyperionDisplay(int width, int height);
    virtual ~HyperionDisplay();
protected:
    virtual void drawPoint(int x, int y, char ch, const Color& color);
private:
    int m_width;
    int m_height;
    int m_bufferSize;
    void clearBuffer();
    uint8_t *m_buffer;
};

#endif /* defined(__tetra_table__HyperionDispay__) */
