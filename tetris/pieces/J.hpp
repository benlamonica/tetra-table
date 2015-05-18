//
//  J.h
//  TetraTable
//
//  Created by Ben La Monica on 1/13/15.
//  Copyright (c) 2015 Benjamin Alan La Monica. All rights reserved.
//

#ifndef __TetraTable__J__
#define __TetraTable__J__

#include <stdio.h>
#include "TetraTablePiece.hpp"

class J : public TetraTablePiece {
public:
    J();
    virtual ~J();
    
private:
    typedef TetraTablePiece super;
    
};
#endif /* defined(__TetraTable__J__) */
