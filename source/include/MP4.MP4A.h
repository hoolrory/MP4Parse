//
//  MP4.MP4A.h
//  MP4Parse
//
//  Created by Hool, Rory on 8/4/16.
//  Copyright © 2016 RoryHool. All rights reserved.
//

#ifndef _MP4_MP4A_H_
#define _MP4_MP4A_H_
#pragma once

#include "mp4.h"
#include "MP4.ContainerAtom.h"
#include "MP4.BinaryStream.h"

namespace MP4
{
    class MP4A : public ContainerAtom
    {
    private:
        
        
    protected:
        int _dataReferenceIndex;
        int _channelCount;
        int _sampleSize;
        long _sampleRate;
        int _soundVersion;
        int _compressionId;
        int _packetSize;
        long _samplesPerPacket;
        long _bytesPerPacket;
        long _bytesPerFrame;
        long _bytesPerSample;
        
        int _reserved1;
        long _reserved2;
        
        std::vector<uint8_t> _soundVersion2Data;
        
        //byte[] soundVersion2Data;
        
        
    public:
        
        
        MP4A( void ) : ContainerAtom( ( char * )"MP4A" )
        {}
        
        std::string subtitle() { return "Audio Sample Entry Box"; }
        std::string description( int depth );
        void processData( MP4::BinaryStream * stream, size_t length );
        int getLength( void );
    };
}

#endif /* _MP4_MP4A_H_ */
