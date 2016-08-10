//
//  MP4.MOOV.cpp
//  MP4Parse
//
//  Created by Hool, Rory on 8/10/16.
//  Copyright © 2016 RoryHool. All rights reserved.
//

#include "MP4.MOOV.h"

using namespace MP4;

std::string MOOV::description( int depth )
{
    std::ostringstream o;
    
    o << std::string(depth, '-') << this->_type << "\n";
    o << std::string(depth+2, ' ') << this->subtitle() << "\n";
    
    for( std::vector<MP4::Atom*>::iterator it = _children.begin(); it != _children.end(); ++it )
    {
        o << ( *it )->description( depth + 1 );
    }
    
    return o.str();
}

void MOOV::processData( MP4::BinaryStream * stream, size_t length )
{
    (void) stream;
    (void) length;
}
