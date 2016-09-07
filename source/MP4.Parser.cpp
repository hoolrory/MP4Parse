/*******************************************************************************
 * Copyright (c) 2011, Jean-David Gadina - www.xs-labs.com
 * Distributed under the Boost Software License, Version 1.0.
 * 
 * Boost Software License - Version 1.0 - August 17th, 2003
 * 
 * Permission is hereby granted, free of charge, to any person or organization
 * obtaining a copy of the software and accompanying documentation covered by
 * this license (the "Software") to use, reproduce, display, distribute,
 * execute, and transmit the Software, and to prepare derivative works of the
 * Software, and to permit third-parties to whom the Software is furnished to
 * do so, all subject to the following:
 * 
 * The copyright notices in the Software and this entire statement, including
 * the above license grant, this restriction and the following disclaimer,
 * must be included in all copies of the Software, in whole or in part, and
 * all derivative works of the Software, unless such copies or derivative
 * works are solely in the form of machine-executable object code generated by
 * a source language processor.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
 * SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
 * FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 ******************************************************************************/
 
/* $Id$ */

#include "MP4.Parser.h"
#include "atoms.h"
#include <stack>
#include <stdio.h>
#include "hex.h"

using namespace MP4;

ParserException::ParserException( void )
{
    this->code = -1;
}

ParserException::ParserException( unsigned int c )
{
    this->code = c;
}

const char * ParserException::what( void ) const throw()
{
    switch( this->code )
    {
        case ParserException::NoFileName:
            
            return "No input file";
    }
    
    return "Unknown exception";
}

Parser::Parser( void )
{
    ParserException e = ParserException( ParserException::NoFileName );
    
    throw e;
}

Parser::Parser( char * filename )
{
    MP4::Atom          * atom;
    MP4::ContainerAtom * parentAtom;
    int                  parentDepth = 0;
    
    std::stack<MP4::ContainerAtom*> previousParents;
   
    _atomFactory = new AtomFactory();
    this->_stream = new BinaryStream( filename );
    this->_file   = new MP4::File();
    FILE * pFile;
    long size = 0;
    this->_verboseLogging = false;
    
    pFile = fopen (filename,"rb");
    if(pFile==NULL) perror ("Error opening file");
    else
    {
        fseek (pFile, 0, SEEK_END);   // non-portable
        size=ftell (pFile);
        fclose (pFile);
    }
    this->_file->setDataLength(size);
    
    if( _verboseLogging )
    {
        std::cout << "File size = " << size <<  "\n";
    }
    
    parentAtom = this->_file;
    
    while( !this->_stream->eof() )
    {
        atom = parseNextAtom();
        
        if ( atom == nullptr ) {
            break;
        }
        
        while( parentAtom->lengthOfChildren() + atom->getLength() > parentAtom->getDataLength()) {
            if( parentDepth == 0 ) {
                break;
            }
            parentAtom = previousParents.top();
            previousParents.pop();
            parentDepth--;
            
            if( _verboseLogging )
            {
                std::cout << " ---- Resetting parent to " << parentAtom->getType() << " at "<< atom->getType() << "\n";
            }
        }
        if( _verboseLogging )
        {
            uint64_t diff = parentAtom->getDataLength() - (parentAtom->lengthOfChildren() + atom->getDataLength()) ;
            std::cout << "Adding child " << atom->getType() << " to parent " << parentAtom->getType() << "\n";
            std::cout << "pA->loc = " << parentAtom->lengthOfChildren() << " a.l = " << atom->getLength() << " pA.gdl = " << parentAtom ->getDataLength() << "\n";
            std::cout << "       remaining = " << diff << "\n";
        }
        parentAtom->addChild(atom);
        
        ContainerAtom *containerAtom = dynamic_cast<ContainerAtom*>( atom );
        if( containerAtom ) {
            previousParents.push(parentAtom);
            parentAtom = containerAtom;
            if( _verboseLogging )
            {
                std::cout << " ---- Setting parent to " << parentAtom->getType() << " \n";
            }
            parentDepth++;
        }
    }
}

MP4::Atom* Parser::parseNextAtom()
{
    std::streampos atomStart = this->_stream->tellg();
    
    uint64_t length = this->_stream->readBigEndianUnsignedInteger();
    if ( this->_stream->eof() ) {
        return nullptr;
    }
    
    uint64_t dataLength = 0;
    char type[ 5 ];
    memset( type, 0, 5 );
    this->_stream->read( ( char * )type, 4 );
    
    uint64_t headerLength = 8;
    
    if( length == 1 )
    {
        headerLength += 8;
        dataLength = this->_stream->readBigEndianUnsignedLong() - 16;
    }
    else
    {
        dataLength = length - 8;
    }
    
    if( _verboseLogging )
    {
        std::cout << "Found " << type << " atom, length = " << dataLength << "\n";
    }
    
    Atom * atom = _atomFactory->instantiateAtom( type );
    std::streampos start = _stream->tellg();
    atom->processData( this->_stream, dataLength );
    uint64_t read = _stream->tellg() - start;
    
    atom->setHeaderLength( headerLength + read );
    atom->setDataLength( dataLength - read );
    
    std::streampos atomEnd = this->_stream->tellg();
    
    atom->setStreamPos(atomStart, atomEnd);
    
    return atom;
}

Parser::~Parser( void )
{
    delete this->_stream;
    delete this->_file;
}

Atom* Parser::getRootAtom( void )
{
    return _file;
}

void Parser::prettyPrint()
{
    prettyPrintAtom( _file, 0 );
}


void Parser::prettyPrintAtom( Atom * atom, int depth )
{
    if( depth != 0 ) {
        std::cout << std::string(depth, '-') << atom->getType() << " ( " << atom->getName() << " )\n";
    }
    
    ContainerAtom *containerAtom = dynamic_cast<ContainerAtom*>( atom );
    if( containerAtom ) {
        for( std::vector<MP4::Atom*>::iterator it = containerAtom->getChildren().begin(); it != containerAtom->getChildren().end(); ++it )
        {
            prettyPrintAtom( ( *it ), depth+1 );
        }
    }
}


std::string Parser::getBytes( Atom * atom )
{
    this->_stream->clear();
    this->_stream->seekg(atom->getStartStreamPos());
    
    std::ostringstream o1;
    std::ostringstream o2;
    
    while( this->_stream->tellg() != atom->getEndStreamPos() ) {
        char s[1];
        memset(s, 0, 1);
        this->_stream->read((char *)s, 1);
        
        if ( s[0] == '\0' ) {
            o1 << '.';
        } else {
            o1 << s[0];
        }
        o2 << hex(s[0]) << " ";
    }
    return o1.str() + "\n\n" + o2.str();
}
