//
//  MP4.ILST.cpp
//  MP4Parse
//
//  Created by Hool, Rory on 8/5/16.
//  Copyright © 2016 RoryHool. All rights reserved.
//

#include "MP4.MDIA.h"
#include "hex.h"

using namespace MP4;

std::string MDIA::description( int depth )
{
    std::ostringstream o;
    o << ContainerAtom::description(depth);
    return o.str();
}

void MDIA::processData( MP4::BinaryStream * stream, size_t length )
{
    (void) stream;
    (void) length;
}
