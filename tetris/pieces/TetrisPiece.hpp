//
//  TetrisPiece.hpp
//  tetris
//
//  Created by La Monica Family on 12/28/14.
//  Copyright (c) 2014 Benjamin Alan La Monica. All rights reserved.
//

#ifndef tetris_TetrisPiece_hpp
#define tetris_TetrisPiece_hpp

#include <memory>

/*
   ████████ ||||

     ██     T
   ██████  TTT
 
   ██      J
   ██████  JJJ
 
       ██    L
   ██████  LLL
 
   ████    QQ
   ████    QQ
 

 
     ████   SS
   ████    SS

*/

class TetrisPiece {
public:
    typedef std::shared_ptr<TetrisPiece> Ptr;
    TetrisPiece();
    virtual ~TetrisPiece();
    void rotateLeft();
    void rotateRight();
    virtual void getMask(int &width, int &height, char *mask);
protected:
    int m_rotation;
    char name;
};

#endif
