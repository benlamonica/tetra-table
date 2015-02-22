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
#include <vector>
#include <memory>
class Color {
public:
    Color(uint8_t red, uint8_t green, uint8_t blue) : r(red), g(green), b(blue) { }
    uint8_t r;
    uint8_t g;
    uint8_t b;
    int key() const { return ((r << 16) | (g << 8) | b); }
};

class TetrisPiece {
public:
    typedef std::shared_ptr<TetrisPiece> Ptr;
    virtual ~TetrisPiece();
    void rotateLeft();
    void rotateRight();
    const std::string& getMask() const;
    const Color& getColor() const;
    char getRep() const;
    int getX() const;
    int getY() const;
    void moveDown();
    void moveLeft();
    void moveRight();
    int getWidth() const;
    int getHeight() const;
    void setLocation(int x, int y);
protected:
    TetrisPiece(std::vector<std::string> masks, char rep, short m_red, short m_green, short m_blue, int width, int height);
    int m_rotation;
    std::vector<std::string> m_masks;
    Color m_color;
    char m_rep; // the character representing this piece in the board grid
    int m_x; // x pos on the board, 0 being far left
    int m_y; // y pos on the board, 0 being top of the board
    int m_width;
    int m_height;
};

#endif
