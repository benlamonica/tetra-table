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

class TetrisPiece {
public:
    typedef std::shared_ptr<TetrisPiece> Ptr;
private:
    int m_rotation;
    int m_width;
    int m_height;
    char name;
};

#endif
