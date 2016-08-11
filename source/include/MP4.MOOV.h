//
//  MP4.MOOV.h
//  MP4Parse
//
//  Created by Hool, Rory on 8/10/16.
//  Copyright © 2016 RoryHool. All rights reserved.
//

#ifndef _MP4_MOOV_H_
#define _MP4_MOOV_H_
#pragma once

#include "mp4.h"
#include "MP4.ContainerAtom.h"
#include "MP4.BinaryStream.h"

namespace MP4
{
    class MOOV : public ContainerAtom
    {
    private:
        
        
    protected:
        
        
    public:
        
        
        MOOV( void ) : ContainerAtom( ( char * )"MOOV" )
        {}
        
        std::string getName() { return "Movie Box"; }
        std::string description( int depth );
        void processData( MP4::BinaryStream * stream, size_t length );
    };
}

#endif /* _MP4_MP4A_H_ */
