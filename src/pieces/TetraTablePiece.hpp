//
//  TetraTablePiece.hpp
//  TetraTable
//
//  Created by La Monica Family on 12/28/14.
//  Copyright (c) 2014 Benjamin Alan La Monica. All rights reserved.
//

#ifndef TetraTable_TetraTablePiece_hpp
#define TetraTable_TetraTablePiece_hpp

#include <string>
#include <vector>
#include <memory>
#include "TetraTableMove.hpp"

class Color {
public:
    Color(uint8_t red, uint8_t green, uint8_t blue) : r(red), g(green), b(blue) { }
    uint8_t r;
    uint8_t g;
    uint8_t b;
    void writeTo(uint8_t *buf) const { *buf = r; *(buf+1) = g; *(buf+2) = b; }
    int key() const { return ((r << 16) | (g << 8) | b); }
};

class TetraTablePiece {
public:
    typedef std::shared_ptr<TetraTablePiece> Ptr;
    virtual ~TetraTablePiece();
    void rotateLeft();
    void rotateRight();
    const std::string& getMask() const;
    const Color& getColor() const;
    const Color& getGrayColor() const;
    char getRep() const;
    int getX() const;
    int getY() const;
    void moveDown();
    void moveLeft();
    void moveRight();
    int getWidth() const;
    void setLocation(int x, int y);
    void setRotation(int rotation);
protected:
    TetraTablePiece(std::vector<std::string> masks, char rep, const Color &color, const Color &grayColor, int width);
    int m_rotation;
    std::vector<std::string> m_masks;
    Color m_color;
    Color m_grayColor;
    char m_rep; // the character representing this piece in the board grid
    int m_x; // x pos on the board, 0 being far left
    int m_y; // y pos on the board, 0 being top of the board
    int m_width;
};

#endif
