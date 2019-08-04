#ifndef _FILEUTIL_H
#define _FILEUTIL_H

#include <cstring>
#include <sys/cdefs.h>

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


extern BOOL IsFileReadable(const std::string &file_path);

extern long FileSize(const std::string &file_path);

#endif // _FILEUTIL_H
