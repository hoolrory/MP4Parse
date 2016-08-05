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
        
        
    public:
        
        
        MP4A( void ) : ContainerAtom( ( char * )"MP4A" )
        {}
        
        std::string description( int depth );
        void processData( MP4::BinaryStream * stream, size_t length );
        int getLength( void );
    };
}

#endif /* _MP4_MP4A_H_ */
