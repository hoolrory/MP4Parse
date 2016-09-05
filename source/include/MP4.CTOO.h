//
//  MP4.©too.h
//  MP4Parse
//
//  Created by Hool, Rory on 8/5/16.
//  Copyright © 2016 RoryHool. All rights reserved.
//

#ifndef _MP4_ctoo_H_
#define _MP4_ctoo_H_
#pragma once

#include "mp4.h"
#include "MP4.Atom.h"
#include "MP4.BinaryStream.h"

namespace MP4
{
    class CTOO : public Atom
    {
    private:
        
        
    protected:
        
        
    public:
        
        CTOO( void );
        std::string getName() { return "iTunes Encoder"; };
        std::string getContent( void );
        void processData( MP4::BinaryStream * stream, size_t length );
    };
}

#endif /* _MP4_ctoo_H_ */
