//
//  S.hpp
//  TetraTable
//
//  Created by Ben La Monica on 1/13/15.
//  Copyright (c) 2015 Benjamin Alan La Monica. All rights reserved.
//

#ifndef __TetraTable__S__
#define __TetraTable__S__

#include <stdio.h>
#include "TetraTablePiece.hpp"

class S : public TetraTablePiece {
public:
    S();
    virtual ~S();
  
private:
    typedef TetraTablePiece super;

};
#endif /* defined(__TetraTable__S__) */
