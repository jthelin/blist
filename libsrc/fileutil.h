#ifndef _FILEUTIL_H
#define _FILEUTIL_H

#include <sys/cdefs.h>

__BEGIN_DECLS

#ident "%Z% $Id$__ - njt"

/*******************************************************************************
*
* File		:	fileutil.h
*
* Authors	:	Jorgen Thelin
* 
* Abstract	:	File utilities
*    
* Environment   :	NCR UNIX V.4
*
******************************************************************************/

#ifndef BOOL
typedef int BOOL;
#endif


extern BOOL IsFileReadable( const char * fname );
extern long FileSize( const char * fname );

__END_DECLS

#endif _FILEUTIL_H

/* EOF */
