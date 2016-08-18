//
//  MP4.ILST.cpp
//  MP4Parse
//
//  Created by Hool, Rory on 8/5/16.
//  Copyright © 2016 RoryHool. All rights reserved.
//

#include "MP4.TRAF.h"
#include "hex.h"

using namespace MP4;

std::string TRAF::getContent( void )
{
    std::ostringstream o;
    o << ContainerAtom::getContent();
    return o.str();
}

void TRAF::processData( MP4::BinaryStream * stream, size_t length )
{
    (void) stream;
    (void) length;
}
