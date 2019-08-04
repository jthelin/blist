#include <string>
#include <iostream>

#ifndef lint
static std::string ident_proginfo_c = "%Z% $RCSfile$  v$Revision$  $Date$__ - njt";
#endif /* lint */

/*******************************************************************************
*
* File		:	proginfo.h
*
* Authors	:	Jorgen Thelin
* 
* Abstract	:	Program information and sign-on.
*    
* Environment   :	NCR UNIX V.4
*
* Change History:	See bottom of file.
*  
******************************************************************************/

#include "proginfo.h"

void ModuleSignOn(
    const std::string &progName,
    const std::string &progVer,
    const std::string &progReleaseStatus,
    const std::string &progAuthor) {
  std::cerr
      << progName
      << " v" << progVer << ".[" << progReleaseStatus << "]"
      << " (" << progAuthor << ")"
      << std::endl;
}
