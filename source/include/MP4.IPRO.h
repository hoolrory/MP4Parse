//
//  MP4.ILST.h
//  MP4Parse
//
//  Created by Hool, Rory on 8/5/16.
//  Copyright © 2016 RoryHool. All rights reserved.
//

#ifndef _MP4_IPRO_H_
#define _MP4_IPRO_H_
#pragma once

#include "mp4.h"
#include "MP4.ContainerAtom.h"
#include "MP4.BinaryStream.h"

namespace MP4
{
    class IPRO : public ContainerAtom
    {
    private:
        
        
    protected:
        
        
    public:
        
        IPRO( void ) : ContainerAtom( ( char * )"IPRO" )
        {}
        
        std::string subtitle() { return "Item Protection Box"; }
        std::string description( int depth );
        void processData( MP4::BinaryStream * stream, size_t length );
    };
}

#endif /* _MP4_IPRO_H_ */