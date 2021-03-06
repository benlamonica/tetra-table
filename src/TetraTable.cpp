//
//  TetraTable.cpp
//  TetraTable
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
#include "TetraTable.hpp"
#include "display/TetraTableDisplay.hpp"
#include "pieces/J.hpp"
#include "pieces/L.hpp"
#include "pieces/I.hpp"
#include "pieces/O.hpp"
#include "pieces/S.hpp"
#include "pieces/T.hpp"
#include "pieces/Z.hpp"
#include "audio/TetraTableAudio.hpp"
#include "util/TimeUtil.hpp"
#include "input/TetraTableInput.hpp"

TetraTable::~TetraTable() {
    m_inputHandler.reset();
}

using namespace util;

TetraTable::TetraTable(std::shared_ptr<TetraTableDisplay> display, std::shared_ptr<TetraTableAudio> audio) : m_display(display), m_isRunning(true), m_score(0), m_boardHeight(22), m_boardWidth(10), m_dropSpeed(1000 * 1000000), m_lockSpeed(1500 * 1000000), m_shuffler(std::random_device()()), m_dropTime(m_dropSpeed * 1000000), m_lockTime(INT64_MAX), m_aboutToLock(false), m_audio(audio), m_locking(false) {

    resetGame();
};

void TetraTable::setInputHandler(std::shared_ptr<TetraTableInput> inputHandler) {
    m_inputHandler = inputHandler;
}

void TetraTable::resetGame() {
    m_board.clear();
    m_pieces.clear();
    m_heldPiece.reset();
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

void TetraTable::gameover() {
    m_isGameOver.store(true);
    m_currentPiece.reset();
    m_audio->stopMusic();
    
    for (int y = m_boardHeight-1; y >= 0; y--) {
        std::transform(m_board.at(y).begin(), m_board.at(y).end(), m_board.at(y).begin(), ::tolower);
        draw();
        m_audio->playSound(TetraTableAudio::PIECE_FREEZE);
        millisleep(160);
    }
    
    m_audio->playSound(TetraTableAudio::GAME_OVER);
}

void TetraTable::takeNextPiece() {
    fillPieceBag();
    resetDropTime();
    resetLockTime();
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
        return;
    }
    m_shadowY = calculateDropPosition();
    draw();
    m_audio->playSound(TetraTableAudio::NEW_PIECE);
    m_swapped = false;
}

void TetraTable::fillPieceBag() {
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

void TetraTable::resetDropTime(int64_t nowInNs) {
    m_dropTime.store(nowInNs+m_dropSpeed);
}

void TetraTable::resetLockTime() {
    m_lockTime.store(INT64_MAX);
}

void TetraTable::run() {
    while(m_isRunning.load()) {
        if (m_isGameOver.load()) {
            millisleep(50);
            continue;
        }
        int64_t nowInNs = now();
        int64_t lockInNs = m_lockTime.load();
        int64_t dropInNs = m_dropTime.load();
        syslog(LOG_WARNING, "lockInNs = %lld, dropInNs = %lld", (lockInNs-nowInNs), (dropInNs-nowInNs));
        if (dropInNs == -1) {
            millisleep(50);
            continue;
        }
        if (lockInNs <= nowInNs) {
            m_inputHandler->addMove(pieces::DROP);
            resetDropTime(nowInNs);
            resetLockTime();
        } else if (!m_aboutToLock.load() && dropInNs <= nowInNs) {
            m_inputHandler->addMove(pieces::DOWN_AUTODROP);
            resetDropTime(nowInNs);
        } else {
            int64_t timeToSleep = std::min(std::min(lockInNs,dropInNs) - nowInNs, (int64_t)m_lockSpeed);
            struct timespec sleepTime = {(timeToSleep / 1000000000), timeToSleep % 1000000000};
            // sleep until it's time to check the lock
            nanosleep(&sleepTime, NULL);
            continue;
        }
    }
}

void TetraTable::draw(bool redraw) {
    // prevent draws from being called at the same time from different threads
    m_display->drawNextPiece(m_nextPiece);
    m_display->drawHeldPiece(m_heldPiece);
    m_display->drawLevel(m_level);
    m_display->drawScore(m_score);
    m_display->drawRemainingLines(m_linesLeft);
    m_display->drawBoard(m_board, m_currentPiece, m_shadowY);
    if (redraw) {
        m_display->redraw();
    } else {
        m_display->flush();
    }
}

void TetraTable::lockPiece() {
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
        m_audio->playSound(TetraTableAudio::LOCK);
    }
    takeNextPiece();
    m_locking = false;
}

void TetraTable::checkForLock() {
    if (m_currentPiece->getY() < m_shadowY) {
        m_aboutToLock.store(false);
        m_lockTime.store(INT64_MAX);
    } else {
        m_aboutToLock.store(true);
        m_lockTime.store(now() + m_lockSpeed);
    }
}

void TetraTable::moveLeft() {
    if (m_currentPiece && !collisionAt(m_currentPiece, m_currentPiece->getX()-1, m_currentPiece->getY())) {
        m_currentPiece->moveLeft();
        m_shadowY = calculateDropPosition();
        checkForLock();
    }
}

void TetraTable::moveRight() {
    if (m_currentPiece && !collisionAt(m_currentPiece, m_currentPiece->getX()+1, m_currentPiece->getY())) {
        m_currentPiece->moveRight();
        m_shadowY = calculateDropPosition();
        checkForLock();
    }
}

void TetraTable::moveDown(bool autoDrop) {
    if (m_currentPiece) {
        if (!autoDrop) {
            m_score++;
        }
        
        resetDropTime();
        if (m_currentPiece->getY() >= m_shadowY) {
            drop(true);
            return;
        }
        
        m_currentPiece->moveDown();

        if (m_currentPiece->getY() == m_shadowY) {
            checkForLock();
        }
    }
}

void TetraTable::drop(bool hard) {
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
            m_audio->playSound(TetraTableAudio::HARD_DROP);
            lockPiece();
        } else {
            m_audio->playSound(TetraTableAudio::SOFT_DROP);
            checkForLock();
        }
    }
}

void TetraTable::holdPiece() {
    // only allow 1 swap per drop... this variable is reset after we get a new piece from the bag
    if (m_swapped || m_aboutToLock) {
        return;
    }
    
    std::swap(m_heldPiece, m_currentPiece);
    if (!m_currentPiece) {
        takeNextPiece();
    } else {
        m_currentPiece->setLocation(4, 0);
        m_currentMask = m_currentPiece->getMask();
        if (collisionAtLog(m_currentPiece, 4, 0)) {
            gameover();
            return;
        }
        m_shadowY = calculateDropPosition();
    }
    m_swapped = true;
}
void TetraTable::rotate(pieces::Move move) {
    if (m_currentPiece) {
        m_audio->playSound(TetraTableAudio::ROTATE);
        
        if (move == pieces::Move::ROTATE_RIGHT) {
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
        } else {
            if (move == pieces::Move::ROTATE_RIGHT) {
                m_currentPiece->rotateLeft();
            } else {
                m_currentPiece->rotateRight();
            }
            m_currentMask = m_currentPiece->getMask();
        }
    }
}

void TetraTable::quit() {
    syslog(LOG_WARNING, "exiting TetraTable");
    m_isRunning.store(false);
}

void TetraTable::levelUp() {
    m_level++;
    m_linesLeft = m_level * 5;
    m_dropSpeed -= (m_dropSpeed*.25);
    m_lockSpeed -= (m_lockSpeed*.10);
}

void TetraTable::checkForLevelUp() {
    if (m_linesLeft <= 0) {
        levelUp();
    }
}

int TetraTable::removeLines(int y) {
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
        m_audio->playSound(TetraTableAudio::REMOVE_LINE);
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
            draw();
            millisleep(75);
        }
        
        // and then remove them
        
        for (LineMap::iterator lineIter = lines.begin(); lineIter != lines.end(); ++lineIter) {
            BoardType::iterator boardIter = m_board.begin() + lineIter->first;
            m_board.erase(boardIter);
            m_board.push_front(std::string(m_boardWidth, ' '));
        }
        
        static const int scoreForLines[] = {1, 3, 5, 8};
        
        // is this line clear difficult?
        bool isDifficult = lines.size() == 4; // TetraTable! yes. We don't support t-spins yet, so nothing else to check yet.
        
        double difficultMultiplier = 1.0;
        if (isDifficult && m_wasLastLineClearDifficult) {
            difficultMultiplier = 1.5;
        }
        int score = scoreForLines[lines.size()-1] * 100 * m_level * difficultMultiplier;
        if (lines.size() == 4) {
            m_audio->playSound(TetraTableAudio::FOUR_LINES);
            if (m_wasLastLineClearDifficult) {
                score *= 1.5;
            }
            m_wasLastLineClearDifficult = true;
        }
        
        m_linesLeft -= scoreForLines[lines.size()-1] * difficultMultiplier;
        m_score += score;
        
        checkForLevelUp();
    }
    
    return (int) lines.size(); // cast: we'll never have more than 4 lines removed
}

// check to see if we have a collision at a given spot
bool TetraTable::collisionAtLog(TetraTablePiece::Ptr piece, int pieceX, int pieceY) {
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


// check to see if we have a collision at a given spot
bool TetraTable::collisionAt(TetraTablePiece::Ptr piece, int pieceX, int pieceY) {
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
int TetraTable::calculateDropPosition() {
    int shadowY = m_currentPiece->getY(); // start at the piece and go down
    while (!collisionAt(m_currentPiece, m_currentPiece->getX(), shadowY)) {
        shadowY++; // haven't found a collision yet, move the check down a line
    }
    
    return shadowY - 1;
}
