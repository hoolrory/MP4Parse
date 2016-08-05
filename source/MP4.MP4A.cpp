//
//  MP4.MP4A.cpp
//  MP4Parse
//
//  Created by Hool, Rory on 8/4/16.
//  Copyright © 2016 RoryHool. All rights reserved.
//

#include "MP4.MP4A.h"
#include "hex.h"

using namespace MP4;

std::string MP4A::description( int depth )
{
    std::ostringstream o;
    
    o << ContainerAtom::description(depth);
    // o << std::string(depth, '-') << this->_type << "\n";
    
    return o.str();
}

void MP4A::processData( MP4::BinaryStream * stream, size_t length )
{
    FullBox::processData(stream, length);
    stream->ignore( length - 43 );
}

int MP4A::getLength()
{
    return Atom::getLength();
}
