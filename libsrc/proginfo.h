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
extern const std::string ProgDate; /* Program date stamp */
/**
 * Output sign-on message to stderr, based on the contents of the parameters.
 * @param progName - Program name.
 * @param progVer - Program version.
 * @param progReleaseStatus - Program release status. (Optional)
 * @param progAuthor - Program author. (Optional)
 * @param progDate - Program date stamp. (Optional)
 */
extern std::ostream& ModuleSignOn(
    const std::string &progName,
    const std::string &progVer,
    const std::string &progReleaseStatus = nullptr,
    const std::string &progAuthor = nullptr,
    const std::string &progDate = nullptr
);

/**
 * Function:	ProgramSignOn
 * Output sign-on message for the program, based on the contents of the variables:
 * ProgName, ProgVer, ProgReleaseStatus, ProgAuthor, and ProgDate,
 * which should be defined by the main program.
 */
inline std::ostream& ProgramSignOn() {
  return ModuleSignOn(
      ProgName,
      ProgVer,
      ProgReleaseStatus,
      ProgAuthor,
      ProgDate);
}
#endif // _PROGINFO_H
