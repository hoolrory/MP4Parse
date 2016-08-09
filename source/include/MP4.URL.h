//
//  MP4.URL.h
//  MP4Parse
//
//  Created by Hool, Rory on 8/4/16.
//  Copyright © 2016 RoryHool. All rights reserved.
//

#ifndef _MP4_URL_H_
#define _MP4_URL_H_
#pragma once

#include "mp4.h"
#include "MP4.FullBox.h"
#include "MP4.BinaryStream.h"

namespace MP4
{
    class URL : public FullBox
    {
    private:
        
        
    protected:
        
    public:
        
        URL( void );
        
        std::string subtitle() { return "Data Entry URL Box"; }
        std::string description( int depth );
        void processData( MP4::BinaryStream * stream, size_t length );
    };
}

#endif /* _MP4_URL_H_ */
