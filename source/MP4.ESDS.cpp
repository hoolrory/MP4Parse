//
//  MP4.ESDS.cpp
//  MP4Parse
//
//  Created by Hool, Rory on 8/4/16.
//  Copyright © 2016 RoryHool. All rights reserved.
//

#include "MP4.ESDS.h"

using namespace MP4;

ESDS::ESDS( void )
{
    this->_type.append( "ESDS" );
}

std::string ESDS::getContent( void )
{
    std::ostringstream o;
    
    
    
    
    return o.str();
}

void ESDS::processData( MP4::BinaryStream * stream, size_t length )
{
    FullBox::processData( stream, length );
    stream->ignore( length - 4 );
}
