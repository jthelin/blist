#pragma once

#include <iostream>
#include <sstream>
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
  std::string Name;          /* Program Name */
  std::string Desc;          /* Program Description */
  std::string Version;       /* Program Version */
  std::string Author;        /* Program Author */
  std::string ReleaseDate;   /* Program Release Date */
  std::string ReleaseStatus; /* Program Release Status eg. Beta, Released */
};

/**
 * ModuleSignOn - Output sign-on message to stderr, based on the contents of the parameters.
 * @param progName - Program name.
 * @param progVer - Program version.
 * @param progReleaseStatus - Program release status. (Optional)
 * @param progAuthor - Program author. (Optional)
 * @param progDate - Program date stamp. (Optional)
 */
inline std::ostream& ModuleSignOn(const std::string& progName,
                                  const std::string& progVer,
                                  const std::string& progReleaseStatus = "",
                                  const std::string& progAuthor        = "",
                                  const std::string& progDate          = "")
{
  std::stringstream out;

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

  return std::cerr << out.str() << std::endl;
}

/**
 * ProgramSignOn - Output sign-on message for the program, based on the contents of the variables:
 * ProgName, ProgVer, ProgReleaseStatus, ProgAuthor, and ProgDate,
 * which should be defined by the main program.
 */
inline std::ostream& ProgramSignOn(const ProgInfo& program_info, const bool announce = false)
{
  auto& out = ModuleSignOn(
    program_info.Name, program_info.Version, program_info.ReleaseStatus, program_info.Author, program_info.ReleaseDate);

  if (announce) {
    out << program_info.Name << " - " << program_info.Desc << std::endl << std::endl;
    out.flush();
  }

  return out;
}
