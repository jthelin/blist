/*
      ShowTime 1.0
    SSTRING.H

       declares the class string, and StringList

    Copyright(c), All Rights Reserved, AHB: 30/04/93
*/
#if !defined(__SSTRING_H)
#define __SSTRING_H

#include <sys/types.h>
#include <string.h>
#include "list.h"

class string {

    char *data;

public:

    string( const char * );
    string( unsigned int );
    string();
    string( const string & );
    string& operator = ( const char * );
    string& operator = ( const string & );
    ~string();
    void replace( const char * );
    void replace( unsigned int );
    friend const char *str( const string & );
    friend char *STR( const string & );
    char& operator[]( int i );
    const char& operator[]( int i ) const ;
    friend int operator == ( const string &, const char * );
    friend int operator == ( const string &, const string & );
    friend int operator != ( const string &, const char * );
    friend int operator != ( const string &, const string & );
    operator const char * ( void )  const
    { return (const char *) data; };
    operator char * ( void ) 
    { return (char *) data; };
};

#endif // __SSTRING_H
