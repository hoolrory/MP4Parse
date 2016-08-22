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

std::string MP4A::getContent( void )
{
    std::ostringstream o;
    
    o << "Data Reference Index:      " << this->_dataReferenceIndex << "\n";
    o << "Bytes Per Frame:           " << this->_bytesPerFrame << "\n";
    o << "Bytes Per Packet:          " << this->_bytesPerPacket << "\n";
    o << "Bytes Per Sample:          " << this->_bytesPerSample << "\n";
    o << "Channel Count:             " << this->_channelCount << "\n";
    o << "Compression Id:            " << this->_compressionId << "\n";
    o << "Packet Size:               " << this->_packetSize << "\n";
    o << "Reserved 1:                " << this->_reserved1 << "\n";
    o << "Reserved 2:                " << this->_reserved2 << "\n";
    o << "Sample Rate:               " << this->_sampleRate << "\n";
    o << "Sample Size:               " << this->_sampleSize << "\n";
    o << "Samples Per Packet:        " << this->_samplesPerPacket << "\n";
    o << "Sound Version:             " << this->_soundVersion << "\n";
    
    char const hex_chars[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };
    
    std::string soundVersionDataHex = "";
    
    for( std::vector<uint8_t>::iterator it = _soundVersion2Data.begin(); it != _soundVersion2Data.end(); ++it )
    {
        soundVersionDataHex += hex_chars[ ( (* it) & 0xF0 ) >> 4 ];
        soundVersionDataHex += hex_chars[ ( (* it) & 0x0F ) >> 0 ];
        soundVersionDataHex += ", ";
    }
    o << "Sound Version 2 Data:      " << soundVersionDataHex << "\n";
    
    return o.str();
}

void MP4A::processData( MP4::BinaryStream * stream, size_t length )
{
    stream->ignore(6);
    _dataReferenceIndex = stream->readBigEndianUnsignedShort();
    
    _soundVersion = stream->readBigEndianUnsignedShort();
    _reserved1 = stream->readBigEndianUnsignedShort();
    _reserved2 = stream->readBigEndianUnsignedInteger();
    
    _channelCount = stream->readBigEndianUnsignedShort();
    _sampleSize = stream->readBigEndianUnsignedShort();
    _compressionId = stream->readBigEndianUnsignedShort();
    _packetSize = stream->readBigEndianUnsignedShort();
    
    _sampleRate = stream->readBigEndianUnsignedInteger() >> 16;
    
    int skip = 0;
    if (_soundVersion == 1) {
        _samplesPerPacket = stream->readBigEndianUnsignedInteger();
        _bytesPerPacket = stream->readBigEndianUnsignedInteger();
        _bytesPerFrame = stream->readBigEndianUnsignedInteger();
        _bytesPerSample = stream->readBigEndianUnsignedInteger();
        skip = 16;
    } else if (_soundVersion == 2) {
        
        _samplesPerPacket = stream->readBigEndianUnsignedInteger();
        _bytesPerPacket = stream->readBigEndianUnsignedInteger();
        _bytesPerFrame = stream->readBigEndianUnsignedInteger();
        _bytesPerSample = stream->readBigEndianUnsignedInteger();
        
        for(int i = 0; i << 20; i++) {
            _soundVersion2Data.push_back(stream->readUnsignedChar());
        }
        
        skip = 36;
    }
    
    stream->ignore(length - 28 - skip);
}

int MP4A::getLength()
{
    return Atom::getLength();
}
