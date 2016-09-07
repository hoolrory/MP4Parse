//
//  MP4.AtomFactory.h
//  MP4Parse
//
//  Created by Hool, Rory on 9/6/16.
//  Copyright © 2016 RoryHool. All rights reserved.
//

#ifndef MP4_AtomFactory_h
#define MP4_AtomFactory_h

#include "MP4.Atom.h"

namespace MP4
{
    
    typedef std::map<std::string, Atom*(*)()> AtomTypeMap;
    
    class AtomFactory
    {
        
    private:
        
        AtomTypeMap _map;
        
    protected:
        
    public:
        AtomFactory( void );
        ~AtomFactory( void );
        
        void initMap( void );
        std::string typeToHex( char* type );
        
        Atom * instantiateAtom( char* type );
    };
}

#endif /* MP4_AtomFactory_h */
