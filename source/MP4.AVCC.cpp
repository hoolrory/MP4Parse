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

std::string AVCC::getContent( void )
{
    std::ostringstream o;
    
    
    
    o << "Configuration Version:    " << this->_configurationVersion << "\n";
    o << "AVC Level Indication:     " << this->_avcLevelIndication   << "\n";
    o << "AVC Profile Indication:   " << this->_avcProfileIndication << "\n";
    o << "Profile Compatibility:    " << this->_profileCompatibility << "\n";
    o << "Bit Depth Chroma Minus 8: " << this->_bitDepthChromaMinus8 << "\n";
    o << "Bit Depth Luma Minus 8:   " << this->_bitDepthLumaMinus8   << "\n";
    o << "Chroma Format:            " << this->_chromaFormat         << "\n";
    o << "Length Size Minus One:    " << this->_lengthSizeMinusOne   << "\n";
    
    char const hex_chars[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };
    
    std::string pps;
    for( std::vector<std::vector<uint8_t> >::iterator it = _pictureParameterSets.begin(); it != _pictureParameterSets.end(); ++it )
    {
        std::vector<uint8_t> set = ( * it );
        for( std::vector<uint8_t>::iterator it2 = set.begin(); it2 != set.end(); ++it2 )
        {
            pps += hex_chars[ ( (* it2) & 0xF0 ) >> 4 ];
            pps += hex_chars[ ( (* it2) & 0x0F ) >> 0 ];
            pps += ", ";
        }
    }
    pps = pps.substr(0, pps.size()-2);
    
    o << "Picture Parameter Sets:   " << pps << "\n";
    
    std::string sps;
    for( std::vector<std::vector<uint8_t> >::iterator it = _sequenceParameterSets.begin(); it != _sequenceParameterSets.end(); ++it )
    {
        std::vector<uint8_t> set = ( * it );
        for( std::vector<uint8_t>::iterator it2 = set.begin(); it2 != set.end(); ++it2 )
        {
            sps += hex_chars[ ( (* it2) & 0xF0 ) >> 4 ];
            sps += hex_chars[ ( (* it2) & 0x0F ) >> 0 ];
            sps += ", ";
        }
    }
    sps = sps.substr(0, sps.size()-2);
    o << "Sequence Parameter Sets:  " << sps   << "\n";
    
    return o.str();
}

inline int createMask(int a, int b)
{
    int r = 0;
    for (int i=7-a; i>=(7-b); i--)
    {
        r |= 1 << i;
    }
    
    return r;
}

void AVCC::processData( MP4::BinaryStream * stream, size_t length )
{
    std::streampos start = stream->tellg();
    
    _configurationVersion = stream->readUnsignedChar();
    _avcProfileIndication = stream->readUnsignedChar();
    _profileCompatibility = stream->readUnsignedChar();
    _avcLevelIndication =   stream->readUnsignedChar();
    
    _lengthSizeMinusOne = stream->readSignedChar() & createMask(6, 7);
    _numberOfSequenceParameterSets = stream->readSignedChar() & createMask(3,7);
    
    for( int i = 0; i < _numberOfSequenceParameterSets; i++) {
        std::vector<uint8_t> set;
        uint16_t sequenceParameterSetLength = stream->readBigEndianUnsignedShort();
        for( int j = 0; j < sequenceParameterSetLength; j++ ) {
            set.push_back(stream->readUnsignedChar());
        }
        _sequenceParameterSets.push_back( set );
    }
    
    _numberOfPictureParameterSets = stream->readUnsignedChar();
    for( int i = 0; i < _numberOfPictureParameterSets; i++) {
        std::vector<uint8_t> set;
        uint16_t pictureParameterSetLength = stream->readBigEndianUnsignedShort();
        for( int j = 0; j < pictureParameterSetLength; j++ ) {
            set.push_back(stream->readUnsignedChar());
        }
        _pictureParameterSets.push_back(set);
    }
    
    std::streampos read = stream->tellg() - start;
    
    int remaining = (int) ( length - read );
    
    bool hasExt = remaining >= 4;
    if ( hasExt && (_avcProfileIndication == 100 || _avcProfileIndication == 110 || _avcProfileIndication == 122 || _avcProfileIndication == 144) ) {
        
        _chromaFormat = stream->readSignedChar() & createMask(6, 7);
        _bitDepthLumaMinus8 = stream->readSignedChar() & createMask(5, 7);
        _bitDepthChromaMinus8 = stream->readSignedChar() & createMask(5, 7);
        
        long numOfSequenceParameterSetExt = stream->readUnsignedChar();
        for (int i = 0; i < numOfSequenceParameterSetExt; i++) {
            std::vector<uint8_t> set;
            int sequenceParameterSetExtLength = stream->readBigEndianUnsignedShort();
            for( int j = 0; j < sequenceParameterSetExtLength; j++ ) {
                set.push_back(stream->readUnsignedChar());
            }
            _sequenceParameterSetExts.push_back(set);
        }
        
    } else {
        _chromaFormat = -1;
        _bitDepthLumaMinus8 = -1;
        _bitDepthChromaMinus8 = -1;
    }
}
