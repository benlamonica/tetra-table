//
//  Tetris.h
//  tetris
//
//  Created by La Monica Family on 12/28/14.
//  Copyright (c) 2014 Benjamin Alan La Monica. All rights reserved.
//

#ifndef __tetris__Tetris__
#define __tetris__Tetris__

#include <stdio.h>
#include <deque>
#include <memory>
#include <random>
#include <chrono>
#include <mutex>
#include <atomic>
#include "pieces/TetrisPiece.hpp"
#include "pieces/TetrisMove.hpp"
#include "util/TimeUtil.hpp"

class TetrisInput;
class TetrisDisplay;
class TetrisAudio;

class Tetris {
public:
    virtual ~Tetris();
    Tetris(std::shared_ptr<TetrisDisplay> display, std::shared_ptr<TetrisAudio> audio);
    void moveLeft();
    void moveRight();
    void moveDown(bool autoDrop = false);
    void drop(bool hard = false);
    void draw(bool redraw = false);
    void rotate(tetris::Move move);
    void holdPiece();
    void run();
    void quit();
    void setInputHandler(std::shared_ptr<TetrisInput> inputHandler);
    
private:
    void lockPiece();
    bool collisionAtLog(TetrisPiece::Ptr piece, int pieceX, int pieceY);
    bool collisionAt(TetrisPiece::Ptr piece, int pieceX, int pieceY);
    int calculateDropPosition();
    void fillPieceBag();
    void takeNextPiece();
    void checkForLock();
    int removeLines(int y);
    void gameover();
    void resetGame();
    void checkForLevelUp();
    void levelUp();
    void resetDropTime(int64_t nowInNs = tetris::TimeUtil::now());
    void resetLockTime();

    std::deque<TetrisPiece::Ptr> m_pieces;
    std::shared_ptr<TetrisDisplay> m_display;
    std::atomic<bool> m_isRunning;
    typedef std::deque<std::string> BoardType;
    BoardType m_board;
    TetrisPiece::Ptr m_currentPiece;
    TetrisPiece::Ptr m_nextPiece;
    TetrisPiece::Ptr m_heldPiece;
    std::string m_currentMask;
    int m_shadowY;
    int m_boardHeight;
    std::atomic<int> m_score;
    int m_boardWidth;
    long m_dropSpeed; // ms between each line dropped
    long m_lockSpeed;
    int m_level;
    int m_linesLeft;
    std::mt19937 m_shuffler;
    std::atomic<int64_t> m_lockTime;
    std::atomic<bool> m_aboutToLock;
    std::atomic<int64_t> m_dropTime;
    std::atomic<bool> m_isGameOver;
    std::atomic<bool> m_wasLastLineClearDifficult;
    std::shared_ptr<TetrisAudio> m_audio;
    std::atomic<bool> m_locking; // true while performing a lock
    std::atomic<bool> m_swapped;
    std::shared_ptr<TetrisInput> m_inputHandler; // used to inject movements onto the same thread as other movements
};

#endif /* defined(__tetris__Tetris__) */
