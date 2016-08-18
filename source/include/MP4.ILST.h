//
//  MP4.ILST.h
//  MP4Parse
//
//  Created by Hool, Rory on 8/5/16.
//  Copyright © 2016 RoryHool. All rights reserved.
//

#ifndef _MP4_ILST_H_
#define _MP4_ILST_H_
#pragma once

#include "mp4.h"
#include "MP4.ContainerAtom.h"
#include "MP4.BinaryStream.h"

namespace MP4
{
    class ILST : public ContainerAtom
    {
    private:
        
        
    protected:
        
        
    public:
        
        ILST( void ) : ContainerAtom( ( char * )"ILST" )
        {}
        
        std::string getName() { return "iTunes Meta Data Box"; }
        std::string getContent( void );
        void processData( MP4::BinaryStream * stream, size_t length );
    };
}

#endif /* _MP4_ILST_H_ */
