//
//  MP4.ESDS.h
//  MP4Parse
//
//  Created by Hool, Rory on 8/4/16.
//  Copyright © 2016 RoryHool. All rights reserved.
//

#ifndef _MP4_ESDS_H_
#define _MP4_ESDS_H_
#pragma once

#include "mp4.h"
#include "MP4.FullBox.h"
#include "MP4.BinaryStream.h"

namespace MP4
{
    class ESDS : public FullBox
    {
    private:
        
        
    protected:
        
        
    public:
        
        ESDS( void );
        
        std::string getName() { return "ES Descriptor Box"; }
        std::string getContent( void );
        void processData( MP4::BinaryStream * stream, size_t length );
    };
}

#endif /* _MP4_ESDS_H_ */
