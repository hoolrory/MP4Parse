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
        
        
    public:
        
        AVCC( void );
        
        std::string description( int depth );
        void processData( MP4::BinaryStream * stream, size_t length );
    };
}

#endif /* _MP4_AVCC_H_ */
