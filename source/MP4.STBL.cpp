//
//  MP4.ILST.cpp
//  MP4Parse
//
//  Created by Hool, Rory on 8/5/16.
//  Copyright © 2016 RoryHool. All rights reserved.
//

#include "MP4.STBL.h"
#include "hex.h"

using namespace MP4;

std::string STBL::getContent( void )
{
    std::ostringstream o;
    
    return o.str();
}

void STBL::processData( MP4::BinaryStream * stream, size_t length )
{
    (void) stream;
    (void) length;
}
