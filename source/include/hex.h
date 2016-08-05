//
//  hex.h
//  MP4Parse
//
//  Created by Hool, Rory on 8/4/16.
//  Copyright © 2016 RoryHool. All rights reserved.
//

#ifndef hex_h
#define hex_h
#pragma once

#include "MP4.BinaryStream.h"

struct HexCharStruct
{
    unsigned char c;
    HexCharStruct(unsigned char _c) : c(_c) { }
};

inline std::ostream& operator<<(std::ostream& o, const HexCharStruct& hs)
{
    return (o << std::hex << (int)hs.c);
}

inline HexCharStruct hex(unsigned char _c)
{
    return HexCharStruct(_c);
}

inline void dump(std::string tag, char* c, int length)
{
    
    std::cout << tag << " = ";
    
    for( int i = 0; i < length; i++ ) {
        std::cout << hex(c[i]) << " ";
    }
    std::cout << "\n";

}

inline void readAndRewind(std::string tag, MP4::BinaryStream * stream)
{
    char s[20];
    memset(s, 0, 20);
    stream->read((char *)s, 20);
    dump(tag, (char *) s, 20);
    std::streampos pos = stream->tellg();
    pos.operator-=(20);
    stream->seekg(pos);
}

#endif /* hex_h */
