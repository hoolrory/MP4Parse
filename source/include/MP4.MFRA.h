//
//  MP4.ILST.h
//  MP4Parse
//
//  Created by Hool, Rory on 8/5/16.
//  Copyright © 2016 RoryHool. All rights reserved.
//

#ifndef _MP4_MFRA_H_
#define _MP4_MFRA_H_
#pragma once

#include "mp4.h"
#include "MP4.ContainerAtom.h"
#include "MP4.BinaryStream.h"

namespace MP4
{
    class MFRA : public ContainerAtom
    {
    private:
        
        
    protected:
        
        
    public:
        
        MFRA( void ) : ContainerAtom( ( char * )"MFRA" )
        {}
        
        std::string getName() { return "Movie Fragment Random Access"; }
        std::string getContent( void );
        void processData( MP4::BinaryStream * stream, uint64_t length );
    };
}

#endif /* _MP4_MFRA_H_ */
