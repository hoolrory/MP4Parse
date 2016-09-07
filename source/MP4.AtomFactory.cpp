//
//  MP4.AtomFactory.cpp
//  MP4Parse
//
//  Created by Hool, Rory on 9/6/16.
//  Copyright © 2016 RoryHool. All rights reserved.
//

#include <stdio.h>
#include "atoms.h"
#include "MP4.AtomFactory.h"

using namespace MP4;

template<typename T> Atom * createInstance() { return new T; }

AtomFactory::AtomFactory( void )
{
    initMap();
}

AtomFactory::~AtomFactory( void )
{
    
}

Atom* AtomFactory::instantiateAtom( char* type )
{
    Atom* atom = NULL;
    std::string typeString = std::string( type );
    
    if( _map.find(typeString) != _map.end() ) {
        atom = _map[typeString]();
    }
    if( atom == NULL ) {
        std::string typeHex = typeToHex( type );
        
        if ( typeHex.compare( "A9746F6F00" ) == 0 )
        {
            atom = new CTOO();
        }
        else
        {
            std::cout << "Got unknown atom " << type << "\n";
            atom = new UnknownAtom( type );
        }
    }
    
    return atom;
}


std::string AtomFactory::typeToHex( char* type )
{
    char const hex_chars[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };
    
    std::string typeHex;
    for( int i = 0; i < 5; ++i )
    {
        char const byte = type[i];
        
        typeHex += hex_chars[ ( byte & 0xF0 ) >> 4 ];
        typeHex += hex_chars[ ( byte & 0x0F ) >> 0 ];
    }
    
    return typeHex;
}

void AtomFactory::initMap( void )
{
    _map["auth"] = &createInstance<AUTH>;
    _map["avc1"] = &createInstance<AVC1>;
    _map["avcC"] = &createInstance<AVCC>;
    _map["bxml"] = &createInstance<BXML>;
    _map["clef"] = &createInstance<CLEF>;
    _map["co64"] = &createInstance<CO64>;
    _map["cslg"] = &createInstance<CSLG>;
    _map["cprt"] = &createInstance<CPRT>;
    _map["ctts"] = &createInstance<CTTS>;
    _map["dinf"] = &createInstance<DINF>;
    _map["dref"] = &createInstance<DREF>;
    _map["edts"] = &createInstance<EDTS>;
    _map["elst"] = &createInstance<ELST>;
    _map["enof"] = &createInstance<ENOF>;
    _map["esds"] = &createInstance<ESDS>;
    _map["free"] = &createInstance<FREE>;
    _map["frma"] = &createInstance<FRMA>;
    _map["ftyp"] = &createInstance<FTYP>;
    _map["hdlr"] = &createInstance<HDLR>;
    _map["hmhd"] = &createInstance<HMHD>;
    _map["iinf"] = &createInstance<IINF>;
    _map["iloc"] = &createInstance<ILOC>;
    _map["ilst"] = &createInstance<ILST>;
    _map["imif"] = &createInstance<IMIF>;
    _map["iods"] = &createInstance<IODS>;
    _map["ipmc"] = &createInstance<IPMC>;
    _map["ipro"] = &createInstance<IPRO>;
    _map["mdat"] = &createInstance<MDAT>;
    _map["mdhd"] = &createInstance<MDHD>;
    _map["mdia"] = &createInstance<MDIA>;
    _map["mehd"] = &createInstance<MEHD>;
    _map["meta"] = &createInstance<META>;
    _map["mfhd"] = &createInstance<MFHD>;
    _map["mfra"] = &createInstance<MFRA>;
    _map["mfro"] = &createInstance<MFRO>;
    _map["minf"] = &createInstance<MINF>;
    _map["moof"] = &createInstance<MOOF>;
    _map["moov"] = &createInstance<MOOV>;
    _map["mp4a"] = &createInstance<MP4A>;
    _map["mvex"] = &createInstance<MVEX>;
    _map["mvhd"] = &createInstance<MVHD>;
    _map["padb"] = &createInstance<PADB>;
    _map["pdin"] = &createInstance<PDIN>;
    _map["pitm"] = &createInstance<PITM>;
    _map["prof"] = &createInstance<PROF>;
    _map["sbgp"] = &createInstance<SBGP>;
    _map["schi"] = &createInstance<SCHI>;
    _map["schm"] = &createInstance<SCHM>;
    _map["sdtp"] = &createInstance<SDTP>;
    _map["sgpd"] = &createInstance<SGPD>;
    _map["sinf"] = &createInstance<SINF>;
    _map["skip"] = &createInstance<SKIP>;
    _map["smhd"] = &createInstance<SMHD>;
    _map["stbl"] = &createInstance<STBL>;
    _map["stco"] = &createInstance<STCO>;
    _map["stdp"] = &createInstance<STDP>;
    _map["stsc"] = &createInstance<STSC>;
    _map["stsd"] = &createInstance<STSD>;
    _map["stsh"] = &createInstance<STSH>;
    _map["stss"] = &createInstance<STSS>;
    _map["stsz"] = &createInstance<STSZ>;
    _map["stts"] = &createInstance<STTS>;
    _map["stz2"] = &createInstance<STZ2>;
    _map["subs"] = &createInstance<SUBS>;
    _map["tapt"] = &createInstance<TAPT>;
    _map["tfhd"] = &createInstance<TFHD>;
    _map["tfra"] = &createInstance<TFRA>;
    _map["tkhd"] = &createInstance<TKHD>;
    _map["traf"] = &createInstance<TRAF>;
    _map["trak"] = &createInstance<TRAK>;
    _map["tref"] = &createInstance<TREF>;
    _map["trex"] = &createInstance<TREX>;
    _map["trun"] = &createInstance<TRUN>;
    _map["udta"] = &createInstance<UDTA>;
    _map["uuid"] = &createInstance<UUID>;
    _map["url "] = &createInstance<URL>;
    _map["vmhd"] = &createInstance<VMHD>;
    _map["wide"] = &createInstance<WIDE>;
    _map["xml "] = &createInstance<XML>;
}

