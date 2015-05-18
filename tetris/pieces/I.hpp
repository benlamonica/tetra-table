//
//  I.h
//  TetraTable
//
//  Created by Ben La Monica on 1/13/15.
//  Copyright (c) 2015 Benjamin Alan La Monica. All rights reserved.
//

#ifndef __TetraTable__I__
#define __TetraTable__I__

#include <stdio.h>
#include "TetraTablePiece.hpp"

class I : public TetraTablePiece {
public:
    I();
    virtual ~I();
private:
    typedef TetraTablePiece super;

};

#endif /* defined(__TetraTable__I__) */
