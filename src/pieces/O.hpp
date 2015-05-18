//
//  O.hpp
//  TetraTable
//
//  Created by Ben La Monica on 1/13/15.
//  Copyright (c) 2015 Benjamin Alan La Monica. All rights reserved.
//

#ifndef __TetraTable__O__
#define __TetraTable__O__

#include <stdio.h>
#include "TetraTablePiece.hpp"

class O : public TetraTablePiece {
public:
    O();
    virtual ~O();

private:
    typedef TetraTablePiece super;

};
#endif /* defined(__TetraTable__O__) */
