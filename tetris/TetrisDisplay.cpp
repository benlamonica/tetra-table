//
//  TetrisDisplay.cpp
//  tetris
//
//  Created by Ben La Monica on 1/14/15.
//  Copyright (c) 2015 Benjamin Alan La Monica. All rights reserved.
//

#include <syslog.h>
#include <map>
#include "TetrisDisplay.hpp"
#include "pieces/TetrisPiece.hpp"
#include "pieces/J.hpp"
#include "pieces/L.hpp"
#include "pieces/I.hpp"
#include "pieces/O.hpp"
#include "pieces/S.hpp"
#include "pieces/T.hpp"
#include "pieces/Z.hpp"

void TetrisDisplay::drawBoard(char board[10][20], TetrisPiece::Ptr currentPiece, int shadowY) {
    char mask[7] = "      ";
    
    currentPiece->getMask(mask);
    syslog(LOG_WARNING, "drawing piece: %c with color %x at (%d,%d)", currentPiece->getRep(), currentPiece->getColor().key(), currentPiece->getX(), currentPiece->getY());
    for (int x = 0; x < 10; x++) {
        for (int y = 0; y < 20; y++) {
            int maskPos = (x - currentPiece->getX())+((y - currentPiece->getY())*currentPiece->getWidth());
            if (x >= currentPiece->getX() && x < (currentPiece->getX()+currentPiece->getWidth())) {
                if (y >= currentPiece->getY() && y < (currentPiece->getY()+currentPiece->getHeight()) && mask[maskPos] != ' ') {
                    drawPoint(x, y, currentPiece->getRep(), currentPiece->getColor());
                } else if (y >= shadowY && y < shadowY+currentPiece->getHeight()) {
//                    drawPoint(x, y, '.', getColor('.'));
                }else {
                    drawPoint(x, y, board[x][y], getColor(board[x][y]));
                }
            } else {
                drawPoint(x, y, board[x][y], getColor(board[x][y]));
            }
        }
    }
}

const Color& TetrisDisplay::getColor(char pieceType) {
    typedef std::map<char, std::shared_ptr<Color> > PieceMap;
    static PieceMap colorMap = {
        {'L', std::make_shared<Color>(L().getColor())},
        {'J', std::make_shared<Color>(J().getColor())},
        {'I', std::make_shared<Color>(I().getColor())},
        {'O', std::make_shared<Color>(O().getColor())},
        {'S', std::make_shared<Color>(S().getColor())},
        {'T', std::make_shared<Color>(T().getColor())},
        {'Z', std::make_shared<Color>(Z().getColor())},
        {'.', std::make_shared<Color>(5,5,5)} // color of the shadow piece
    };
    
    PieceMap::const_iterator it = colorMap.find(pieceType);
    if (colorMap.find(pieceType) != colorMap.end()) {
        return *(it->second);
    }
    
    // we didn't find that piece in the map, so return black color;
    static const Color c(0,0,0);
    return c;
}