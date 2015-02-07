//
//  TetrisPiece.cpp
//  tetris
//
//  Created by Ben La Monica on 1/14/15.
//  Copyright (c) 2015 Benjamin Alan La Monica. All rights reserved.
//

#include "TetrisPiece.hpp"

TetrisPiece::~TetrisPiece() {
    
}

TetrisPiece::TetrisPiece(char rep, short red, short green, short blue, int width, int height) : m_rotation(0), m_color(red, green, blue), m_rep(rep), m_width(width), m_height(height), m_x(4), m_y(0) {
    
}

void TetrisPiece::rotateLeft() {
    m_rotation += 90;
    if (m_rotation > 360) {
        m_rotation -= 360;
    }
    std::swap(m_width, m_height);
}

void TetrisPiece::rotateRight() {
    m_rotation -= 90;
    if (m_rotation < 0) {
        m_rotation += 360;
    }
    std::swap(m_width, m_height);
}

const Color& TetrisPiece::getColor() const {
    return m_color;
}

void TetrisPiece::setLocation(int x, int y) {
    m_x = x;
    m_y = y;
}

char TetrisPiece::getRep() const {
    return m_rep;
}

int TetrisPiece::getWidth() const {
    return m_width;
}

int TetrisPiece::getHeight() const {
    return m_height;
}

int TetrisPiece::getX() const {
    return m_x;
}

int TetrisPiece::getY() const {
    return m_y;
}

void TetrisPiece::moveLeft() {
    if (m_x > 0) {
        m_x--;
    }
}

void TetrisPiece::moveRight() {
    if ((m_x + getWidth()) < 10) {
        m_x++;
    }
    
}

void TetrisPiece::moveDown() {
    m_y++;
}
