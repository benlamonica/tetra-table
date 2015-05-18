//
//  TetraTableDisplay.hpp
//  TetraTable
//
//  Created by La Monica Family on 12/28/14.
//  Copyright (c) 2014 Benjamin Alan La Monica. All rights reserved.
//

#ifndef TetraTable_TetraTableDisplay_hpp
#define TetraTable_TetraTableDisplay_hpp

#include <deque>
#include "../pieces/TetraTablePiece.hpp"

typedef std::deque<std::string> BoardType;

class TetraTableDisplay {
public:
    void drawBoard(const BoardType &board, TetraTablePiece::Ptr currentPiece, int shadowY);
    virtual void drawNextPiece(TetraTablePiece::Ptr nextPiece) = 0;
    virtual void drawHeldPiece(TetraTablePiece::Ptr heldPiece) = 0;
    virtual void drawScore(int score) = 0;
    virtual void drawLevel(int level) = 0;
    virtual void drawRemainingLines(int remainingLines) = 0;
    virtual void flush() = 0;
    virtual void redraw() = 0;
    virtual ~TetraTableDisplay();
protected:
    virtual void drawPoint(int x, int y, char ch, const Color& color) = 0;
    const Color& getColor(char pieceType);
};

#endif
