/*
list.h

a unidirectional linked-list pure virtual class to form a base for
other list classes because this installation does not support
templates -that would have been neater.

Adesola H Bankole 1/07/93
*/
#if !defined(__LIST_H)
#define __LIST_H

#include <sys/types.h> // for use of boolean_t

struct slink {

    void* data;
    slink(void* Data=0): data(Data), next(0) { }
    slink* next;
    friend class slist;
};

class slist {

protected:

    ulong i, n; // the current element and the total number of elements
    slink* tail;
    virtual int cmp( void*, void* ) = 0;

public:

    slist(): tail( 0 ), n( 0 ), i( 0 ) {}
    slist( void* D );

    void _insert( void* D );
    void _append( void* D );
    void* _remove();
    void* _next( boolean_t forward ); // forward ? forwards : backwards
    void _deleteList();
};

#endif // __LIST_H
