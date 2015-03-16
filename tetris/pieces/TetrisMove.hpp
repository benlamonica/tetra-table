//
//  TetrisMove.hpp
//  tetris
//
//  Created by Ben La Monica on 2/24/15.
//  Copyright (c) 2015 Benjamin Alan La Monica. All rights reserved.
//

#ifndef tetris_TetrisMove_hpp
#define tetris_TetrisMove_hpp

namespace tetris {
    
enum Move {
    NONE,
    LEFT,
    RIGHT,
    DOWN,
    DROP,
    ROTATE_LEFT,
    ROTATE_RIGHT,
    HOLD_PIECE,
    QUIT
};

}

#endif
