#ifndef _UTILMSG_H
#define _UTILMSG_H

/*  UTILMSG.H  */

#include <sys/cdefs.h>

__BEGIN_DECLS

#ident "%Z% $Id$__ - njt"

/************************************************************************/
/* Print an error message from the format-string FORMAT                 */
/* with optional extra args as with printf.                                                        */
/************************************************************************/

extern void  error( char *format, ... );


/************************************************************************/
/* Print an error message containing the string TEXT, then exit.                  */
/************************************************************************/

extern void  fatal( char *message );


/************************************************************************/
/* Like printf, except if buffer_messages is set                        */
/*  then save the message and print later.                                                          */
/************************************************************************/

extern void  message( char *format, char *arg1, char *arg2, ... );


/************************************************************************/
/* malloc a block of memory,                                                                                    */
/* with fatal error message if we can't do it.                                                        */
/************************************************************************/

extern void *xmalloc ( unsigned size );


/************************************************************************/
/* realloc a block of memory,                                                                                      */
/* with fatal error message if we can't do it.                                                        */
/************************************************************************/

extern void *xrealloc( void *old, unsigned int size );


/************************************************************************/
/* Concatenate three strings, returning a newly malloc'd string.            */
/************************************************************************/

extern char *concat( char *s1, char *s2, char *s3);


__END_DECLS

#endif
