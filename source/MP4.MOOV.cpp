//
//  MP4.MOOV.cpp
//  MP4Parse
//
//  Created by Hool, Rory on 8/10/16.
//  Copyright © 2016 RoryHool. All rights reserved.
//

#include "MP4.MOOV.h"

using namespace MP4;

std::string MOOV::getContent( void )
{
    std::ostringstream o;
    
    return o.str();
}

void MOOV::processData( MP4::BinaryStream * stream, uint64_t length )
{
    (void) stream;
    (void) length;
}
