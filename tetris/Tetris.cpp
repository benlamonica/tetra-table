//
//  Tetris.cpp
//  tetris
//
//  Created by La Monica Family on 12/28/14.
//  Copyright (c) 2014 Benjamin Alan La Monica. All rights reserved.
//

#include <time.h>
#include <algorithm>
#include <random>
#include <chrono>
#include <map>
#include <syslog.h>
#include "Tetris.hpp"
#include "display/TetrisDisplay.hpp"
#include "pieces/J.hpp"
#include "pieces/L.hpp"
#include "pieces/I.hpp"
#include "pieces/O.hpp"
#include "pieces/S.hpp"
#include "pieces/T.hpp"
#include "pieces/Z.hpp"
#include "audio/TetrisAudio.hpp"

namespace {
    int64_t now() {
        using namespace std::chrono;
        return duration_cast<nanoseconds>(high_resolution_clock::now().time_since_epoch()).count();
    }
    
    void millisleep(int millis) {
        struct timespec sleepTime = {(millis / 1000), (millis % 1000) * 1000000};
        nanosleep(&sleepTime, NULL);
    }
}

Tetris::~Tetris() {
    
}

Tetris::Tetris(std::shared_ptr<TetrisDisplay> display, std::shared_ptr<TetrisAudio> audio) : m_display(display), m_isRunning(true), m_score(0), m_boardHeight(20), m_boardWidth(10), m_dropSpeed(1000 * 1000000), m_lockSpeed(1000 * 1000000), m_shuffler(std::random_device()()), m_dropTime(m_dropSpeed * 1000000), m_lockTime(INT64_MAX), m_aboutToLock(false), m_audio(audio), m_locking(false) {

    resetGame();
};

void Tetris::resetGame() {
    m_board.clear();
    m_pieces.clear();
    m_dropSpeed = 1000 * 1000000;
    m_lockSpeed = 1000 * 1000000;
    m_dropTime.store(m_dropSpeed * 1000000);
    m_lockTime.store(INT64_MAX);
    m_aboutToLock.store(false);
    m_level = 1;
    m_linesLeft = 5;
    m_nextPiece.reset();
    m_score = 0;
    for (int i = 0; i < m_boardHeight; i++) {
        m_board.push_back(std::string(m_boardWidth, ' '));
    }
  
    m_isGameOver.store(false);
    m_audio->playMusic();
    takeNextPiece();
    
}

void Tetris::gameover() {
    m_isGameOver.store(true);
    m_currentPiece.reset();
    m_audio->stopMusic();
    
    for (int y = m_boardHeight-1; y >= 0; y--) {
        std::transform(m_board.at(y).begin(), m_board.at(y).end(), m_board.at(y).begin(), ::tolower);
        draw();
        m_audio->playSound(TetrisAudio::PIECE_FREEZE);
        millisleep(100);
    }
    
    m_audio->playSound(TetrisAudio::GAME_OVER);
}

void Tetris::takeNextPiece() {
    syslog(LOG_WARNING, "take next piece at: %lld", now());
    fillPieceBag();
    m_dropTime.store(now() + m_dropSpeed);
    m_lockTime.store(INT64_MAX);
    m_aboutToLock.store(false);
    if (!m_nextPiece) {
        m_nextPiece = m_pieces.front();
        m_pieces.pop_front();
    }
    fillPieceBag();
    m_currentPiece = m_nextPiece;
    m_nextPiece = m_pieces.front();
    m_pieces.pop_front();
    m_currentPiece->setLocation(4, 0);
    m_currentMask = m_currentPiece->getMask();
    if (collisionAtLog(m_currentPiece, 4, 0)) {
        gameover();
        logBoard();
        return;
    }
    m_shadowY = calculateDropPosition();
    draw();
    m_audio->playSound(TetrisAudio::NEW_PIECE);
    m_swapped = false;
}

void Tetris::fillPieceBag() {
    if (m_pieces.empty()) {
        m_pieces.push_back(std::make_shared<J>());
        m_pieces.push_back(std::make_shared<L>());
        m_pieces.push_back(std::make_shared<I>());
        m_pieces.push_back(std::make_shared<O>());
        m_pieces.push_back(std::make_shared<S>());
        m_pieces.push_back(std::make_shared<T>());
        m_pieces.push_back(std::make_shared<Z>());
        
        std::shuffle(m_pieces.begin(), m_pieces.end(), m_shuffler);
    }
}

void Tetris::run() {
    while(m_isRunning.load()) {
        if (m_isGameOver.load()) {
            millisleep(50);
            continue;
        }
        int64_t lockInNs = 0;
        int64_t dropInNs = 0;
        {
            std::lock_guard<std::recursive_mutex> guard(m_eventMutex);
            lockInNs = m_lockTime.load();
            dropInNs = m_dropTime.load();
        } // unlock the mutex
        if (dropInNs == -1) {
            millisleep(50);
            continue;
        }
        int64_t nowInNs = now();
        if (lockInNs <= nowInNs || (dropInNs <= nowInNs && m_aboutToLock.load())) {
            syslog(LOG_WARNING, "dropInNs: %lld lockInNs: %lld nowInNs: %lld aboutToLock: %s", dropInNs, lockInNs, nowInNs, m_aboutToLock.load() ? "true" : "false");
            lockPiece();
        } else if (dropInNs <= nowInNs) {
            syslog(LOG_WARNING, "dropInNs: %lld nowInNs: %lld", dropInNs, nowInNs);
            moveDown(true);
        } else {
            int64_t timeToSleep = std::min(std::min(lockInNs,dropInNs) - nowInNs, (int64_t)m_lockSpeed);
            struct timespec sleepTime = {(timeToSleep / 1000000000), timeToSleep % 1000000000};
            // sleep until it's time to check the lock
            nanosleep(&sleepTime, NULL);
            continue;
        }
    }
}

void Tetris::draw() {
    m_display->drawNextPiece(m_nextPiece);
    m_display->drawHeldPiece(m_heldPiece);
    m_display->drawLevel(m_level);
    m_display->drawScore(m_score);
    m_display->drawRemainingLines(m_linesLeft);
    m_display->drawBoard(m_board, m_currentPiece, m_shadowY);
    m_display->flush();
}

void Tetris::lockPiece() {
    // block the event loop from running while we manipulate the playing field
    std::lock_guard<std::recursive_mutex> guard(m_eventMutex);

    syslog(LOG_WARNING, "Locking piece : %c at [%d,%d]", m_currentPiece->getRep(), m_currentPiece->getX(), m_currentPiece->getY());

    m_lockTime.store(INT64_MAX);
    m_dropTime.store(-1);
    m_aboutToLock.store(false);
    m_locking.store(true);
    int width = m_currentPiece->getWidth();
    
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < width; y++) {
            if (m_currentMask.at(x+(y*m_currentPiece->getWidth())) != ' ') {
                m_board.at(m_currentPiece->getY() + y).at(m_currentPiece->getX() + x) = m_currentPiece->getRep();
            }
        }
    }

    int y = m_currentPiece->getY();
    m_currentPiece.reset(); // make this null, so that when we draw the screen for animations, it doesn't draw the piece again

    if (removeLines(y) == 0) {
        m_audio->playSound(TetrisAudio::LOCK);
    }
    takeNextPiece();
    m_locking = false;
}

void Tetris::checkForLock() {
    if (m_currentPiece->getY() < m_shadowY) {
        m_aboutToLock.store(false);
        m_lockTime.store(INT64_MAX);
    } else {
        m_aboutToLock.store(true);
        m_lockTime.store(now() + m_lockSpeed);
    }
}

void Tetris::moveLeft() {
    if (m_currentPiece && !collisionAt(m_currentPiece, m_currentPiece->getX()-1, m_currentPiece->getY())) {
        m_currentPiece->moveLeft();
        m_shadowY = calculateDropPosition();
        checkForLock();
        draw();
    }
}

void Tetris::moveRight() {
    if (m_currentPiece && !collisionAt(m_currentPiece, m_currentPiece->getX()+1, m_currentPiece->getY())) {
        m_currentPiece->moveRight();
        m_shadowY = calculateDropPosition();
        checkForLock();
        draw();
    }
}

void Tetris::moveDown(bool autoDrop) {
    if (m_currentPiece) {
        if (!autoDrop) {
            m_score++;
        }
        
        m_dropTime.store(now()+m_dropSpeed);
        if (m_currentPiece->getY() >= m_shadowY) {
            drop(true);
            return;
        }
        
        m_currentPiece->moveDown();

        if (m_currentPiece->getY() == m_shadowY) {
            checkForLock();
        }
        draw();
    }
}

void Tetris::drop(bool hard) {
    if (m_isGameOver.load()) {
        resetGame();
        return;
    }

    bool isLocked = false;
    if (m_locking.compare_exchange_strong(isLocked, true) && m_currentPiece) {
        while (m_currentPiece->getY() < m_shadowY) {
            m_currentPiece->moveDown();
            m_score+=2;
        }
        
        if(hard) {
            m_audio->playSound(TetrisAudio::HARD_DROP);
            syslog(LOG_WARNING, "Hard Drop Lock");
            lockPiece();
        } else {
            m_audio->playSound(TetrisAudio::SOFT_DROP);
            checkForLock();
        }
        draw();
    }
}

void Tetris::holdPiece() {
    // only allow 1 swap per drop... this variable is reset after we get a new piece from the bag
    if (m_swapped) {
        return;
    }
    
    syslog(LOG_WARNING, "swapping piece");
    std::swap(m_heldPiece, m_currentPiece);
    if (!m_currentPiece) {
        takeNextPiece();
    } else {
        m_currentPiece->setLocation(4, 0);
        m_currentMask = m_currentPiece->getMask();
        if (collisionAtLog(m_currentPiece, 4, 0)) {
            gameover();
            logBoard();
            return;
        }
        m_shadowY = calculateDropPosition();
        draw();
    }
    m_swapped = true;
}
void Tetris::rotate(tetris::Move move) {
    if (m_currentPiece) {
        m_audio->playSound(TetrisAudio::ROTATE);
        
        if (move == tetris::Move::ROTATE_RIGHT) {
            m_currentPiece->rotateRight();
        } else {
            m_currentPiece->rotateLeft();
        }
        
        m_currentMask = m_currentPiece->getMask();

        bool isRotateSuccessful = false;
        int offsets[] = {0,1,2,-1,-2};
        // if we can't rotate, see if we can nudge it to the right or left
        for (int i = 0; i < 4; i++) {
            if (!collisionAt(m_currentPiece, m_currentPiece->getX()+offsets[i], m_currentPiece->getY())) {
                m_currentPiece->setLocation(m_currentPiece->getX()+offsets[i], m_currentPiece->getY());
                isRotateSuccessful = true;
                break;
            }
        }

        if (isRotateSuccessful) {
            m_shadowY = calculateDropPosition();
            checkForLock();
            draw();
        } else {
            if (move == tetris::Move::ROTATE_RIGHT) {
                m_currentPiece->rotateLeft();
            } else {
                m_currentPiece->rotateRight();
            }
            m_currentMask = m_currentPiece->getMask();
        }
    }
}

void Tetris::quit() {
    syslog(LOG_WARNING, "exiting tetris");
    m_isRunning.store(false);
}

void Tetris::logBoard() {
    std::string board;
    for (int y = 0; y < m_boardHeight; y++) {
        board.append(m_board.at(y)).append("\n");
    }
    
    syslog(LOG_WARNING, "%s", board.c_str());
}

void Tetris::checkForLevelUp() {
    if (m_linesLeft <= 0) {
        m_level++;
        m_linesLeft = m_level * 5;
        m_dropSpeed -= (m_dropSpeed*.25);
        m_lockSpeed -= (m_lockSpeed*.25);
    }
}

int Tetris::removeLines(int y) {
    typedef std::map<int,std::string> LineMap;
    LineMap lines;
    // first, find the completed lines
    while (y < m_boardHeight) {
        int filledBlocks = 0;
        for (int x = 0; x < m_boardWidth; x++) {
            if (m_board.at(y).at(x) != ' ') {
                filledBlocks++;
            }
        }
        if (filledBlocks == m_boardWidth) {
            lines.insert(std::make_pair(y,m_board.at(y)));
        }
        y++;
    }
    
    if (!lines.empty()) {
        m_audio->playSound(TetrisAudio::REMOVE_LINE);
        // now animate them, as they are about to go away
        for (int i = 0; i < 6; i++) {
            for (LineMap::iterator lineIter = lines.begin(); lineIter != lines.end(); ++lineIter) {
                BoardType::iterator boardIter = m_board.begin() + lineIter->first;
                if (i % 2 == 0) {
                    *boardIter = std::string(m_boardWidth, ' ');
                } else {
                    *boardIter = lineIter->second;
                }
            }
            logBoard();
            draw();
            millisleep(75);
        }
        
        // and then remove them
        
        for (LineMap::iterator lineIter = lines.begin(); lineIter != lines.end(); ++lineIter) {
            BoardType::iterator boardIter = m_board.begin() + lineIter->first;
            m_board.erase(boardIter);
            m_board.push_front(std::string(m_boardWidth, ' '));
        }
        
        static const int scoreForLines[] = {100, 300, 500, 800};
        int score = scoreForLines[lines.size()-1] * m_level;
        if (lines.size() == 4) {
            m_audio->playSound(TetrisAudio::TETRIS);
            if (m_wasLastLineClearDifficult) {
                score *= 1.5;
            }
            m_wasLastLineClearDifficult = true;
        }
        
        m_linesLeft -= lines.size();
        m_score += score;
        
        checkForLevelUp();
    }
    
    return (int) lines.size(); // cast: we'll never have more than 4 lines removed
}

// check to see if we have a collision at a given spot
bool Tetris::collisionAtLog(TetrisPiece::Ptr piece, int pieceX, int pieceY) {
    int width = piece->getWidth();
    syslog(LOG_WARNING, "width: %d", width);
    
    // check to see if our piece will hit another piece
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < width; y++) {
            if (m_currentMask.at(x+(y*m_currentPiece->getWidth())) != ' ') {
                if ((pieceX + x) < 0 || (pieceX + x) >= m_boardWidth) {
                    syslog(LOG_WARNING, "COLLISION: pieceX + x is %d, out of bounds", (pieceX + x));
                    return true;
                }
                if ((pieceY + y) >= m_boardHeight || m_board.at(pieceY + y).at(pieceX + x) != ' ') {
                    syslog(LOG_WARNING, "COLLISION: pieceY + y is %d, board val at [%d,%d] is %c", (pieceY + y), (pieceX + x), (pieceY + y), m_board.at(pieceY + y).at(pieceX + x));
                    return true;
                }
            }
        }
    }
    syslog(LOG_WARNING, "no collision.");
    return false;
}


// check to see if we have a collision at a given spot
bool Tetris::collisionAt(TetrisPiece::Ptr piece, int pieceX, int pieceY) {
    int width = piece->getWidth();
    
    // check to see if our piece will hit another piece
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < width; y++) {
            if (m_currentMask.at(x+(y*m_currentPiece->getWidth())) != ' ') {
                if ((pieceX + x) < 0 || (pieceX + x) >= m_boardWidth) {
                    return true;
                }
                if ((pieceY + y) >= m_boardHeight || m_board.at(pieceY + y).at(pieceX + x) != ' ') {
                    return true;
                }
            }
        }
    }

    return false;
}

// calculates where on the y axis the shadow should start
int Tetris::calculateDropPosition() {
    int shadowY = m_currentPiece->getY(); // start at the piece and go down
    while (!collisionAt(m_currentPiece, m_currentPiece->getX(), shadowY)) {
        shadowY++; // haven't found a collision yet, move the check down a line
    }
    
    return shadowY - 1;
}
