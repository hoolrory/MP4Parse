//
//  MP4.TAPT.h
//  MP4Parse
//
//  Created by Hool, Rory on 9/3/16.
//  Copyright © 2016 RoryHool. All rights reserved.
//
#ifndef _MP4_TAPT_H_
#define _MP4_TAPT_H_
#pragma once

#include "mp4.h"
#include "MP4.ContainerAtom.h"
#include "MP4.BinaryStream.h"

namespace MP4
{
    class TAPT : public ContainerAtom
    {
    private:
        
        
    protected:
        
        
    public:
        
        
        TAPT( void ) : ContainerAtom( ( char * )"TAPT" )
        {}
        
        std::string getName() { return "Track Aperture Mode Dimension Box"; }
        std::string getContent( void );
        void processData( MP4::BinaryStream * stream, size_t length );
    };
}

#endif /* _MP4_TAPT_H_ */
