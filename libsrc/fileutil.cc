#ifndef lint
static char ident_fileutil_c[]="%Z% $Id$__ - njt";
#endif /* lint */

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
* Change History:	See bottom of file.
*  
******************************************************************************/

/* include files */

#include <unistd.h>		/* For access */
#include <stdio.h>		/* For stderr / fprintf */
#include <sys/types.h>		/* For stat */
#include <sys/stat.h>		/* For stat */

#include "fileutil.h"


/******************************************************************************
* Function:	IsFileReadable
*
* Purpose:	Return TRUE if specified file exists and is readable.
******************************************************************************/
BOOL IsFileReadable( const char * fname )
{
	return ( access( fname, F_OK | R_OK ) == 0 );
}


/******************************************************************************
* Function:	FileSize
*
* Purpose:	Return size of specified file (in bytes)
******************************************************************************/
long FileSize( const char * fname )
{
	static char szFunc[] = "FileSize";
	struct stat	stats;

	if ( stat( fname, &stats ) == 0 )
	{
		return (stats.st_size);
	}
	else
	{
		fprintf( stderr,
			"$RCSfile$:%s: Bad return from stat function on file [%s]\n",
			szFunc, fname );
		return -1;
	}
}


/******************************************************************************
 Change History
 ==============

Date          | Name  | Description
--------------+-------+-------------------------------------------------------
28-Mar-96	NJT	v1.1 - Initial version under SCCS control.
22-Apr-96	NJT	v1.2 - Added function FileSize.
******************************************************************************/
/* EOF */
