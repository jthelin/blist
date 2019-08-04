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

std::ostream& ModuleSignOn(
    const std::string &progName,
    const std::string &progVer,
    const std::string &progReleaseStatus,
    const std::string &progAuthor,
    const std::string &progDate) {
  std::ostream& out = std::cerr;

  out << progName << " v" << progVer;

  if (!progReleaseStatus.empty()) {
    out << ".[" << progReleaseStatus << "]";
  }
  if (!progAuthor.empty()) {
    out << " (" << progAuthor << ")";
  }
  if (!progDate.empty()) {
    out << " " << progDate;
  }

  out << std::endl;

  return out;
}
