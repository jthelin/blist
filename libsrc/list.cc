/*
list.C

a unidirectional linked-list class to form a base for other list
classes because this installation does not support templates -that
would have been neater.

Adesola H Bankole 1/07/93
*/
#include <list.h>

#define incrMod(i,n) ((i)= ( (i<n-1) ? (i+1) :(0)   ))
#define decrMod(i,n) ((i)= ( (i>0)   ? (i-1) :(n-1) ))


void* slist::_remove( )
{
    void* res = 0;
    if ( n > 0 )
       {
       res = tail->next->data;
       void* oldHead = tail->next;;
       if ( n == 1 )
		tail = 0;
       else
		tail->next = tail->next->next;
       n--;
       delete oldHead;
       }

    return res;
}

void slist::_insert( void* d )
{
    slink * newLink = new slink( d );

    if ( newLink != 0 )
       {
       if ( tail == 0 )
		tail = newLink;
       else
		newLink -> next = tail -> next;

       tail -> next = newLink;
       n++;
       }
}

void slist::_append( void* d )
{
    if ( tail == 0 )
       {
       tail = new slink( d );
       if ( tail != 0 )
	  {
	  tail -> next = tail;
	  n++;
	  }
       }
    else
       {
       slink* head = tail -> next;
       tail -> next = new slink( d );
       if ( tail->next != 0 )
	  {
          tail = tail -> next;
          tail -> next = head;
	  n++;
	  }
       }
}

void* slist::_next( boolean next )
// need a better version
// should only use this for small lists, with less than a 1000 elements.
{
    if ( n == 0 )
       return 0;
    else
       {
       if ( next )
	  incrMod( i, n );
       else
	  decrMod( i, n );

       slink* iter = tail -> next;
       for ( int j = 0; j < i; j++ ) iter = iter -> next;
       return iter -> data;
       }
}

void slist::_deleteList()
{
   if ( n > 0 )
      {
      slink* ptr = tail->next, *del;
      while ( n > 1 )
	{
	n--;
	del = ptr;
	ptr = ptr->next;
        delete del;
	}
      delete ptr;
      tail = 0;
      n = 0;
      }
}

