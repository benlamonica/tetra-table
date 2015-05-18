//
//  TetraTableMove.hpp
//  TetraTable
//
//  Created by Ben La Monica on 2/24/15.
//  Copyright (c) 2015 Benjamin Alan La Monica. All rights reserved.
//

#ifndef TetraTable_TetraTableMove_hpp
#define TetraTable_TetraTableMove_hpp

namespace pieces {
    
enum Move {
    NONE,
    LEFT,
    RIGHT,
    DOWN,
    DROP,
    ROTATE_LEFT,
    ROTATE_RIGHT,
    HOLD_PIECE,
    QUIT,
    DOWN_AUTODROP
};

}

#endif
