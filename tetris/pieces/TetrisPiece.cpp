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

TetrisPiece::TetrisPiece(std::vector<std::string> masks, char rep, const Color &color, const Color &grayColor, int width) : m_rotation(0), m_masks(masks), m_color(color), m_grayColor(grayColor), m_rep(rep), m_width(width), m_x(4), m_y(0) {
    
}

void TetrisPiece::rotateLeft() {
    m_rotation += 90;
    if (m_rotation > 360) {
        m_rotation -= 360;
    }
}

void TetrisPiece::rotateRight() {
    m_rotation -= 90;
    if (m_rotation < 0) {
        m_rotation += 360;
    }
}

const Color& TetrisPiece::getColor() const {
    return m_color;
}

const Color& TetrisPiece::getGrayColor() const {
    return m_grayColor;
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

int TetrisPiece::getX() const {
    return m_x;
}

int TetrisPiece::getY() const {
    return m_y;
}

void TetrisPiece::moveLeft() {
    m_x--;
}

void TetrisPiece::moveRight() {
    m_x++;
}

const std::string& TetrisPiece::getMask() const {
    return m_masks.at((m_rotation/90) % m_masks.size());
}

void TetrisPiece::moveDown() {
    m_y++;
}
