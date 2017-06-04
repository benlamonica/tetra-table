//
//  HyperionDispay.cpp
//  tetra-table
//
//  Created by Ben La Monica on 6/22/15.
//  Copyright (c) 2015 Benjamin Alan La Monica. All rights reserved.
//

#include "HyperionDisplay.hpp"
#include "../util/Base64.hpp"
#include <iostream>

static const int COLOR_SIZE = 3;

HyperionDisplay::HyperionDisplay(int width, int height) : m_width(width), m_height(height), m_bufferSize(width*height*3), m_buffer(new uint8_t[m_bufferSize]) {
    clearBuffer();
}

HyperionDisplay::~HyperionDisplay() {
    delete[] m_buffer;
}

void HyperionDisplay::clearBuffer() {
    memset(m_buffer, 0, m_bufferSize);
}

void HyperionDisplay::redraw() {

}

void HyperionDisplay::drawNextPiece(TetraTablePiece::Ptr nextPiece) {
    drawPiece(nextPiece, 0, 0);

}

void HyperionDisplay::drawHeldPiece(TetraTablePiece::Ptr heldPiece) {
    drawPiece(heldPiece, 0, 2);
}

void HyperionDisplay::drawScore(int score) {

}

void HyperionDisplay::drawLevel(int level) {

}

void HyperionDisplay::drawRemainingLines(int remainingLines) {

}

/*
 00 ->
 01 <-
 02 ->
 03 <-
 04 ->
 05 <-
 06 ->
 07 <-
 08 ->
 09 <-
 10 ->
 11 <-
 12 ->
 13 <-
 14 ->
 15 <-
 16 ->
 17 <-
 18 ->
 19 <-
   0123456789
 
 Y is Even, is going in order
 Y is Odd, is going reverse order
*/
void HyperionDisplay::flush() {
    std::cout << base64_encode(m_buffer, m_bufferSize) << "\n";
}

void HyperionDisplay::drawPoint(int x, int y, char ch, const Color& color) {
    int pos = y * (m_width * COLOR_SIZE);
    if (y % 2 == 0) {
        pos += x;
    } else {
        pos += ((m_width - x) * COLOR_SIZE);
    }
    
    if (pos < m_bufferSize - COLOR_SIZE) {
        color.writeTo(m_buffer+pos);
    }
}