#ifndef lint
static char ident_fileutil_c[] = "%Z% $Id$__ - njt";
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

#include <unistd.h>    /* For access */
#include <cstdio>    /* For stderr / fprintf */
#include <sys/stat.h>    /* For stat */
#include <string>

#include "fileutil.h"

/******************************************************************************
* Function:	IsFileReadable
*
* Purpose:	Return TRUE if specified file exists and is readable.
******************************************************************************/
bool IsFileReadable(const std::string &file_path) {
  return (access(file_path.c_str(), F_OK | R_OK) == 0);
}


/******************************************************************************
* Function:	FileSize
*
* Purpose:	Return size of specified file (in bytes)
******************************************************************************/
long FileSize(const std::string &file_path) {
  static char szFunc[] = "FileSize";
  struct stat stats{};

  if (stat(file_path.c_str(), &stats) == 0) {
    return (stats.st_size);
  } else {
    fprintf(stderr,
            "$RCSfile$:%s: Bad return from stat function on file [%s]\n",
            szFunc, file_path.c_str());
    return -1;
  }
}


/******************************************************************************
 Change History
 ==============

Date          | Name  | Description
--------------+-------+-------------------------------------------------------
28-Mar-96       NJT     v1.1 - Initial version under SCCS control.
22-Apr-96       NJT     v1.2 - Added function FileSize.
******************************************************************************/
