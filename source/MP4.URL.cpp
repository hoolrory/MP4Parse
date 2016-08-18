//
//  MP4.URL.cpp
//  MP4Parse
//
//  Created by Hool, Rory on 8/4/16.
//  Copyright © 2016 RoryHool. All rights reserved.
//

#include "MP4.URL.h"

using namespace MP4;

URL::URL( void )
{
    this->_type.append( "URL " );
}

std::string URL::getContent( void )
{
    std::ostringstream o;
    
    
    
    
    return o.str();
}

void URL::processData( MP4::BinaryStream * stream, size_t length )
{
    FullBox::processData(stream, length);
}
