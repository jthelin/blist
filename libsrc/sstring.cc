/*
	ShowTime 1.0
	SSTRING.CPP

	defines the class sstring and the struct StringList

	Copyright(c), All Rights Reserved, AHB: 30/04/93
*/
#include <string.h>

#include "sstring.h"

void string::replace( unsigned int len )
{
    if( data != 0 )
	delete [] data;
    if( len != 0 )
	data = new char [ len ];
    else
	data = 0;
}

void string::replace( const char * s )
{
    if( data != 0 )
	delete [] data;
    if( s != 0 )
	{
	data = new char [ strlen(s) + 1 ];
	strcpy( data, s );
	}
    else
	data = 0;
}

string::string( unsigned int len )
{
    data = 0;
    replace( len );
}

string::string( const char *s )
{
    data = 0;
    replace( s );
}

string::string()
{
    data = 0;
}

string::string( const string & x )
{
    data = 0;
    replace ( x.data );
}

string& string::operator = ( const char *s )
{
    replace( s );
    return *this;
}

string& string::operator = ( const string & x )
{
    replace( x.data );
    return *this;
}

string::~string()
{
    replace( (const char *)0 );
}

char& string::operator[]( int i )
{
    return data[i];
}

const char& string::operator[]( int i ) const
{
    return data[i];
}

int operator == ( const string & x, const char * str )
{
    return strcmp( x.data, str );
}

int operator == ( const string & x, const string & y )
{
    return strcmp( x.data, y.data );
}

int operator != ( const string & x, const char * str )
{
    return strcmp( x.data, str ) != 0;
}

int operator != ( const string & x, const string & y )
{
    return strcmp( x.data, y.data ) != 0;
}

char *STR( const string & x )
{
    return x.data;
}

const char *str( const string & x )
{
    return x.data;
}

