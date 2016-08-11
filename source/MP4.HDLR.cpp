/*******************************************************************************
 * Copyright (c) 2011, Jean-David Gadina - www.xs-labs.com
 * Distributed under the Boost Software License, Version 1.0.
 * 
 * Boost Software License - Version 1.0 - August 17th, 2003
 * 
 * Permission is hereby granted, free of charge, to any person or organization
 * obtaining a copy of the software and accompanying documentation covered by
 * this license (the "Software") to use, reproduce, display, distribute,
 * execute, and transmit the Software, and to prepare derivative works of the
 * Software, and to permit third-parties to whom the Software is furnished to
 * do so, all subject to the following:
 * 
 * The copyright notices in the Software and this entire statement, including
 * the above license grant, this restriction and the following disclaimer,
 * must be included in all copies of the Software, in whole or in part, and
 * all derivative works of the Software, unless such copies or derivative
 * works are solely in the form of machine-executable object code generated by
 * a source language processor.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
 * SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
 * FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 ******************************************************************************/
 
/* $Id$ */

#include "MP4.HDLR.h"

using namespace MP4;
          
HDLR::HDLR( void )
{
    this->_type.append( "HDLR" );
}

std::string HDLR::description( int depth )
{
    std::ostringstream o;
    
    o << std::string(depth, '-') << this->_type << "\n";
    o << std::string(depth+2, ' ') << this->getName() << "\n";
    o << "                      - Handler Type:              " << this->_handlerType      << "\n";
    o << "                      - Human Readable Track Type: " << this->getReadableName() << "\n";
    o << "                      - Name:                      " << this->_name             << "\n";
    
    return o.str();
}

void HDLR::processData( MP4::BinaryStream * stream, size_t length )
{
    FullBox::processData( stream, length );
    
    stream->readBigEndianUnsignedInteger();
    char handlerType[ 5 ];
    
    
    memset( handlerType, 0, 5 );
    stream->read( handlerType, 4 );
    _handlerType.append( handlerType );
    
    stream->readBigEndianUnsignedInteger();
    stream->readBigEndianUnsignedInteger();
    stream->readBigEndianUnsignedInteger();
    
    int remaining = length - 24;
    char name[ 2 ];
    while ( remaining > 0 ) {
        memset( name, 0, 2 );
        stream->read( name, 1 );
        _name.append( name );
        remaining--;
    }
}

std::string HDLR::getReadableName() {
    if( _handlerType == "odsm" )
    {
        return "ObjectDescriptorStream - defined in ISO/IEC JTC1/SC29/WG11 - CODING OF MOVING PICTURES AND AUDIO";
    }
    else if( _handlerType == "crsm" )
    {
        return "ClockReferenceStream - defined in ISO/IEC JTC1/SC29/WG11 - CODING OF MOVING PICTURES AND AUDIO";
    }
    else if( _handlerType == "sdsm" )
    {
        return "SceneDescriptionStream - defined in ISO/IEC JTC1/SC29/WG11 - CODING OF MOVING PICTURES AND AUDIO";
    }
    else if( _handlerType == "m7sm" )
    {
        return "MPEG7Stream - defined in ISO/IEC JTC1/SC29/WG11 - CODING OF MOVING PICTURES AND AUDIO";
    }
    else if( _handlerType == "ocsm" )
    {
        return "ObjectContentInfoStream - defined in ISO/IEC JTC1/SC29/WG11 - CODING OF MOVING PICTURES AND AUDIO";
    }
    else if( _handlerType == "ipsm" )
    {
        return "IPMP Stream - defined in ISO/IEC JTC1/SC29/WG11 - CODING OF MOVING PICTURES AND AUDIO";
    }
    else if( _handlerType == "mjsm" )
    {
        return "MPEG-J Stream - defined in ISO/IEC JTC1/SC29/WG11 - CODING OF MOVING PICTURES AND AUDIO";
    }
    else if( _handlerType == "mdir" )
    {
        return "Apple Meta Data iTunes Reader";
    }
    else if( _handlerType == "mp7b" )
    {
        return "MPEG-7 binary XML";
    }
    else if( _handlerType == "mp7t" )
    {
        return "MPEG-7 XML";
    }
    else if( _handlerType == "vide" )
    {
        return "Video Track";
    }
    else if( _handlerType == "soun" )
    {
        return "Sound Track";
    }
    else if( _handlerType == "hint" )
    {
        return "Hint Track";
    }
    else if( _handlerType == "appl" )
    {
        return "Apple specific";
    }
    else if( _handlerType == "meta" )
    {
        return "Timed Metadata track - defined in ISO/IEC JTC1/SC29/WG11 - CODING OF MOVING PICTURES AND AUDIO";
    }
    else
    {
        return "Unknown";
    }
}
