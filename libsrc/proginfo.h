#pragma once

#include <iostream>
#include <string>

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

/**
 * Program Information variables to be defined in the main program module.
 */
struct ProgInfo {
  static std::string Name;          /* Program Name */
  static std::string Desc;          /* Program Description */
  static std::string Version;       /* Program Version */
  static std::string Author;        /* Program Author */
  static std::string ReleaseDate;   /* Program Release Date */
  static std::string ReleaseStatus; /* Program Release Status eg. Beta, Released */
};

/**
 * Output sign-on message to stderr, based on the contents of the parameters.
 * @param progName - Program name.
 * @param progVer - Program version.
 * @param progReleaseStatus - Program release status. (Optional)
 * @param progAuthor - Program author. (Optional)
 * @param progDate - Program date stamp. (Optional)
 */
extern std::ostream& ModuleSignOn(const std::string& progName,
                                  const std::string& progVer,
                                  const std::string& progReleaseStatus = nullptr,
                                  const std::string& progAuthor        = nullptr,
                                  const std::string& progDate          = nullptr);

/**
 * Function:	ProgramSignOn
 * Output sign-on message for the program, based on the contents of the variables:
 * ProgName, ProgVer, ProgReleaseStatus, ProgAuthor, and ProgDate,
 * which should be defined by the main program.
 */
inline std::ostream& ProgramSignOn()
{
  return ModuleSignOn(
    ProgInfo::Name, ProgInfo::Version, ProgInfo::ReleaseStatus, ProgInfo::Author, ProgInfo::ReleaseDate);
}
