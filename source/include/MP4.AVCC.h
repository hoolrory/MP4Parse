//
//  MP4.AVCC.h
//  MP4Parse
//
//  Created by Hool, Rory on 8/4/16.
//  Copyright © 2016 RoryHool. All rights reserved.
//

#ifndef _MP4_AVCC_H_
#define _MP4_AVCC_H_
#pragma once

#include "mp4.h"
#include "MP4.DataAtom.h"
#include "MP4.BinaryStream.h"

namespace MP4
{
    class AVCC : public DataAtom
    {
    private:
        
        
    protected:
        
        float _configurationVersion;
        float _avcProfileIndication;
        float _profileCompatibility;
        float _avcLevelIndication;
        
        int _lengthSizeMinusOne;
        int _numberOfSequenceParameterSets;
        int _numberOfPictureParameterSets;
        
        int _chromaFormat;
        
        int _bitDepthLumaMinus8;
        int _bitDepthChromaMinus8;
        
        std::vector< std::vector< uint8_t > > _sequenceParameterSets;
        std::vector< std::vector< uint8_t > > _pictureParameterSets;
        std::vector< std::vector< uint8_t > > _sequenceParameterSetExts;
        
    public:
        
        AVCC( void );
        
        std::string getName() { return "AVC Configuration"; };
        std::string getContent( void );
        void processData( MP4::BinaryStream * stream, size_t length );
    };
}

#endif /* _MP4_AVCC_H_ */
