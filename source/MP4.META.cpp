//
//  MP4.META.cpp
//  MP4Parse
//
//  Created by Hool, Rory on 8/5/16.
//  Copyright © 2016 RoryHool. All rights reserved.
//

#include "MP4.META.h"
#include "hex.h"

using namespace MP4;

std::string META::getContent( void )
{
    std::ostringstream o;
    
    return o.str();
}

void META::processData( MP4::BinaryStream * stream, size_t length )
{
    (void) stream;
    stream->ignore(length);
}
