//
//  Base64.h
//  tetra-table
//
//  Created by Ben La Monica on 6/22/15.
//  Copyright (c) 2015 Benjamin Alan La Monica. All rights reserved.
//

#ifndef __tetra_table__Base64__
#define __tetra_table__Base64__

#include <stdio.h>
#include <string>

std::string base64_encode(unsigned char const* , unsigned int len);
std::string base64_decode(std::string const& s);

#endif /* defined(__tetra_table__Base64__) */
