//
//  TetrisPiece.hpp
//  tetris
//
//  Created by La Monica Family on 12/28/14.
//  Copyright (c) 2014 Benjamin Alan La Monica. All rights reserved.
//

#ifndef tetris_TetrisPiece_hpp
#define tetris_TetrisPiece_hpp

#include <string>
#include <memory>

class TetrisPiece {
public:
    typedef std::shared_ptr<TetrisPiece> Ptr;
    virtual ~TetrisPiece();
    void rotateLeft();
    void rotateRight();
    virtual void getMask(char *mask) = 0;
    short getRed() const;
    short getGreen() const;
    short getBlue() const;
    char getRep() const;
    int getX() const;
    int getY() const;
    void moveDown();
    void moveLeft();
    void moveRight();
    int getWidth() const;
    int getHeight() const;
protected:
    TetrisPiece(char rep, short m_red, short m_green, short m_blue, int width, int height);
    int m_rotation;
    short m_red;
    short m_green;
    short m_blue;
    char m_rep; // the character representing this piece in the board grid
    int m_x; // x pos on the board, 0 being far left
    int m_y; // y pos on the board, 0 being top of the board
    int m_width;
    int m_height;
};

#endif
