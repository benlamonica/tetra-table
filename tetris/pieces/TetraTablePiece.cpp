//
//  TetraTablePiece.cpp
//  TetraTable
//
//  Created by Ben La Monica on 1/14/15.
//  Copyright (c) 2015 Benjamin Alan La Monica. All rights reserved.
//

#include "TetraTablePiece.hpp"

TetraTablePiece::~TetraTablePiece() {
}

TetraTablePiece::TetraTablePiece(std::vector<std::string> masks, char rep, const Color &color, const Color &grayColor, int width) : m_rotation(90), m_masks(masks), m_color(color), m_grayColor(grayColor), m_rep(rep), m_width(width), m_x(4), m_y(0) {
    
}

void TetraTablePiece::setRotation(int rotation) {
    if (rotation < 360 && rotation % 90 == 0) {
        m_rotation = rotation;
    }
}

void TetraTablePiece::rotateRight() {
    m_rotation += 90;
    if (m_rotation > 360) {
        m_rotation -= 360;
    }
}

void TetraTablePiece::rotateLeft() {
    m_rotation -= 90;
    if (m_rotation < 0) {
        m_rotation += 360;
    }
}

const Color& TetraTablePiece::getColor() const {
    return m_color;
}

const Color& TetraTablePiece::getGrayColor() const {
    return m_grayColor;
}

void TetraTablePiece::setLocation(int x, int y) {
    m_x = x;
    m_y = y;
}

char TetraTablePiece::getRep() const {
    return m_rep;
}

int TetraTablePiece::getWidth() const {
    return m_width;
}

int TetraTablePiece::getX() const {
    return m_x;
}

int TetraTablePiece::getY() const {
    return m_y;
}

void TetraTablePiece::moveLeft() {
    m_x--;
}

void TetraTablePiece::moveRight() {
    m_x++;
}

const std::string& TetraTablePiece::getMask() const {
    return m_masks.at((m_rotation/90) % m_masks.size());
}

void TetraTablePiece::moveDown() {
    m_y++;
}
