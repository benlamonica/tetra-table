//
//  Z.h
//  TetraTable
//
//  Created by Ben La Monica on 1/13/15.
//  Copyright (c) 2015 Benjamin Alan La Monica. All rights reserved.
//

#ifndef __TetraTable__Z__
#define __TetraTable__Z__

#include <stdio.h>
#include "TetraTablePiece.hpp"

class Z : public TetraTablePiece {
public:
    Z();
    virtual ~Z();

private:
    typedef TetraTablePiece super;
    
};
#endif /* defined(__TetraTable__Z__) */
