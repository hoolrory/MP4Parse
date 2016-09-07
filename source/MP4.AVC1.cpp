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

std::string AVC1::getContent( void )
{
    std::ostringstream o;
    
    o << "Data Reference Index:  " << this->_dataReferenceIndex << "\n";
    o << "Predefined:            " << this->_predefined[0] << " " << this->_predefined[1] << " " << this->_predefined[2] << "\n";
    o << "Width:                 " << this->_width << "\n";
    o << "Height:                " << this->_height << "\n";
    o << "Horizontal Resolution: " << this->_horizontalResolution << "\n";
    o << "Vertical Resolution:   " << this->_verticalResolution << "\n";
    o << "Frame Count:           " << this->_frameCount << "\n";
    o << "Depth:                 " << this->_depth << "\n";
    
    return o.str();
}

void AVC1::processData( MP4::BinaryStream * stream, uint64_t length )
{
    (void) length;
    stream->ignore(6);
    
    _dataReferenceIndex = stream->readBigEndianUnsignedShort();
    
    stream->readBigEndianUnsignedShort();
    stream->readBigEndianUnsignedShort();
    
    _predefined[0] = stream->readBigEndianUnsignedInteger();
    _predefined[1] = stream->readBigEndianUnsignedInteger();
    _predefined[2] = stream->readBigEndianUnsignedInteger();
    
    _width = stream->readBigEndianUnsignedShort();
    _height = stream->readBigEndianUnsignedShort();
    
    _horizontalResolution = stream->readBigEndianFixedPoint( 16, 16 );
    _verticalResolution   = stream->readBigEndianFixedPoint( 16, 16 );
    
    stream->readBigEndianUnsignedInteger();
    
    _frameCount = stream->readBigEndianUnsignedShort();
    
    uint8_t compressornameDisplayAbleData = stream->readUnsignedChar();
    if( compressornameDisplayAbleData > 31 ) {
        compressornameDisplayAbleData = 31;
    }
    stream->ignore(compressornameDisplayAbleData);
    
    if( compressornameDisplayAbleData < 31 ) {
        stream->ignore(31 - compressornameDisplayAbleData );
    }
    _depth = stream->readBigEndianUnsignedShort();
    stream->readBigEndianUnsignedShort();
}
