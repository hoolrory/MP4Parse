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
    if( (int)hs.c < 16 ) {
        return (o << 0 << std::hex << (int)hs.c);
    } else {
        return (o << std::hex << (int)hs.c);
    }
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

inline std::string string_to_hex(const std::string& input)
{
    static const char* const lut = "0123456789ABCDEF";
    size_t len = input.length();
    
    std::string output;
    output.reserve(2 * len);
    for (size_t i = 0; i < len; ++i)
    {
        const unsigned char c = input[i];
        output.push_back(lut[c >> 4]);
        output.push_back(lut[c & 15]);
    }
    return output;
}

inline std::string hex_to_string(const std::string& input)
{
    static const char* const lut = "0123456789ABCDEF";
    size_t len = input.length();
    if (len & 1) throw std::invalid_argument("odd length");
    
    std::string output;
    output.reserve(len / 2);
    for (size_t i = 0; i < len; i += 2)
    {
        char a = input[i];
        const char* p = std::lower_bound(lut, lut + 16, a);
        if (*p != a) throw std::invalid_argument("not a hex digit");
        
        char b = input[i + 1];
        const char* q = std::lower_bound(lut, lut + 16, b);
        if (*q != b) throw std::invalid_argument("not a hex digit");
        
        output.push_back(((p - lut) << 4) | (q - lut));
    }
    return output;
}
inline int hexCharToInt(char a){
    if(a>='0' && a<='9')
        return(a-48);
    else if(a>='A' && a<='Z')
        return(a-55);
    else
        return(a-87);
}

inline std::string hexToString(std::string str){
    std::stringstream HexString;
    for(int i=0;i<(int)str.length();i++){
        char a = str.at(i++);
        char b = str.at(i);
        int x = hexCharToInt(a);
        int y = hexCharToInt(b);
        HexString << (char)((16*x)+y);
    }
    return HexString.str();
}

inline int hex_to_int(char c){
    int first = c / 16 - 3;
    int second = c % 16;
    int result = first*10 + second;
    if(result > 9) result--;
    return result;
}

inline int hex_to_ascii(char c, char d){
    int high = hex_to_int(c) * 16;
    int low = hex_to_int(d);
    return high+low;
}

#endif /* hex_h */
