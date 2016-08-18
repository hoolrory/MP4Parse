//
//  MP4.©too.cpp
//  MP4Parse
//
//  Created by Hool, Rory on 8/5/16.
//  Copyright © 2016 RoryHool. All rights reserved.
//

#include <stdio.h>
#include "MP4.CTOO.h"

using namespace MP4;

CTOO::CTOO( void )
{
    this->_type.append( "©TOO" );
}

std::string CTOO::getContent( void )
{
    std::ostringstream o;
    
    return o.str();
}

void CTOO::processData( MP4::BinaryStream * stream, size_t length )
{
    stream->ignore( length );
}
