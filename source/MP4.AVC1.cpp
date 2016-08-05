//
//  MP4.AVC1.cpp
//  MP4Parse
//
//  Created by Hool, Rory on 8/4/16.
//  Copyright © 2016 RoryHool. All rights reserved.
//

#include "MP4.AVC1.h"
#include "hex.h"

using namespace MP4;

std::string AVC1::description( int depth )
{
    std::ostringstream o;
    
    o << std::string(depth, '-') << this->_type << "\n";
    for( std::vector<MP4::Atom*>::iterator it = _children.begin(); it != _children.end(); ++it )
    {
        o << ( *it )->description( depth );
    }
    
    return o.str();
}

void AVC1::processData( MP4::BinaryStream * stream, size_t length )
{
    FullBox::processData(stream, length);
    stream->ignore( 74 );
}

int AVC1::getLength()
{
    return Atom::getLength();
}
