//
//  MP4.AVCC.cpp
//  MP4Parse
//
//  Created by Hool, Rory on 8/4/16.
//  Copyright © 2016 RoryHool. All rights reserved.
//

#include "MP4.AVCC.h"

using namespace MP4;

AVCC::AVCC( void )
{
    this->_type.append( "AVCC" );
}

std::string AVCC::description( int depth )
{
    std::ostringstream o;
    
    o << std::string(depth, '-') << this->_type << "\n";
    
    return o.str();
}

void AVCC::processData( MP4::BinaryStream * stream, size_t length )
{
    stream->ignore( length );
}
