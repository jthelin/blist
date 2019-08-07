#ifndef _UTILMSG_H
#define _UTILMSG_H

/*  UTILMSG.H  */

#include <sys/cdefs.h>

/************************************************************************/
/* Print an error message.                                              */
/************************************************************************/

void error(const std::string& message);

/************************************************************************/
/* Print an error message from the format-string FORMAT                 */
/* with optional extra args as with printf.                             */
/************************************************************************/

extern void error(const std::string& format, ...);

/************************************************************************/
/* Print an error message containing the string TEXT, then exit.        */
/************************************************************************/

extern void fatal(const std::string& message);

/************************************************************************/
/* Like printf, except if buffer_messages is set                        */
/*  then save the message and print later.                              */
/************************************************************************/

extern void message(const std::string &format, const std::string &arg1, const std::string &arg2, ...);

/************************************************************************/
/* malloc a block of memory,                                            */
/* with fatal error message if we can't do it.                          */
/************************************************************************/

extern void *xmalloc(unsigned size);

/************************************************************************/
/* realloc a block of memory,                                           */
/* with fatal error message if we can't do it.                          */
/************************************************************************/

extern void *xrealloc(void *old, unsigned int size);

/************************************************************************/
/* Concatenate three strings, returning a newly malloc'd string.        */
/************************************************************************/

extern std::string concat(char *s1, char *s2, char *s3);

#endif
