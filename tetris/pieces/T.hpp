//
//  T.h
//  TetraTable
//
//  Created by Ben La Monica on 1/13/15.
//  Copyright (c) 2015 Benjamin Alan La Monica. All rights reserved.
//

#ifndef __TetraTable__T__
#define __TetraTable__T__

#include <stdio.h>
#include "TetraTablePiece.hpp"

class T : public TetraTablePiece {
public:
    T();
    virtual ~T();
 
private:
    typedef TetraTablePiece super;

};
#endif /* defined(__TetraTable__T__) */
