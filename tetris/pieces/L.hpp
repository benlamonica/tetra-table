//
//  L.h
//  TetraTable
//
//  Created by Ben La Monica on 1/13/15.
//  Copyright (c) 2015 Benjamin Alan La Monica. All rights reserved.
//

#ifndef __TetraTable__L__
#define __TetraTable__L__

#include <stdio.h>
#include "TetraTablePiece.hpp"

class L : public TetraTablePiece {
public:
    L();
    virtual ~L();

private:
    typedef TetraTablePiece super;

};
#endif /* defined(__TetraTable__L__) */
