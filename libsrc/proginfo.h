#ifndef _PROGINFO_H
#define _PROGINFO_H

#include <sys/cdefs.h>
#include <string>

#ident "%Z% $Id$__ - njt"

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

/* Program Information variables to be defined in the main program module */
extern const std::string ProgName;  /* Program Name */
extern const std::string ProgVer;  /* Program Version */
extern const std::string ProgReleaseStatus;  /* Program Release Status eg. Beta, Released */
extern const std::string ProgAuthor;  /* Program Author */

/**
 * Output sign-on message to stderr, based on the contents of the parameters.
 * @param progName - Program name.
 * @param progVer - Program version.
 * @param progReleaseStatus - Program release status.
 * @param progAuthor - Program author.
 */
extern void ModuleSignOn(
    const std::string &progName,
    const std::string &progVer,
    const std::string &progReleaseStatus,
    const std::string &progAuthor
);

/**
 * Function:	ProgramSignOn
 * Output sign-on message for the program, based on the contents of the variables
 * ProgName, ProgVer, ProgReleaseStatus, and ProgAuthor
 * which should be defined by the main program.
 */
inline void ProgramSignOn() {
  ModuleSignOn(
      ProgName,
      ProgVer,
      ProgReleaseStatus,
      ProgAuthor);
}
#endif // _PROGINFO_H
