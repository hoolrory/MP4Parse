//
//  MP4.ILST.cpp
//  MP4Parse
//
//  Created by Hool, Rory on 8/5/16.
//  Copyright © 2016 RoryHool. All rights reserved.
//

#include "MP4.MVEX.h"
#include "hex.h"

using namespace MP4;

std::string MVEX::getContent( void )
{
    std::ostringstream o;
    
    return o.str();
}

void MVEX::processData( MP4::BinaryStream * stream, uint64_t length )
{
    (void) stream;
    (void) length;
}
