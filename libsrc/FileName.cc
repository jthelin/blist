// Contents ----------------------------------------------------------------
//
//	Contains the implementation for the FileName class
//
// Required libraries:  -lgen
//
// End ---------------------------------------------------------------------

// Interface Declarations --------------------------------------------------
#include "FileName.h"
// End Interface Declarations ----------------------------------------------

// Implementation Dependencies ----------------------------------------------
#include <string>
#include <unistd.h>  // For getcwd
#include <climits>  // For PATH_MAX
#include "fileutil.h"
#include <libgen.h>  // For basename / dirname
#include <sstream>
// End Implementation Dependencies -------------------------------------------


// Summary -----------------------------------------------------------------
//
// Constructor for FileName object
//	Initialises the object data.
//
// Parameters
//	filename
//		The filename we are to use to locate this file.
//
// End ---------------------------------------------------------------------
FileName::FileName(const std::string &filename)
    : fileName(filename) {
  fileExists = IsFileReadable(filename);
}

FileName::FileName(const char *filename)
    : FileName(std::string(filename)) {
}
// End FileName constructor //


// Summary -----------------------------------------------------------------
//
// Constructor for PathName object.
//	Initialises the object data.
//
// Parameters
//	path
//		The filename we are to use to locate this file.
//
// End ---------------------------------------------------------------------
PathName::PathName(const std::string &path)
    : FileName(path), dirName(".") {
  // Split file name into components

  // int pos = path.last_index_of()
  char* tmp_fname = ((char*) (std::string(path)).c_str());
  fileName = std::string(basename(tmp_fname));
  dirName = std::string(dirname(tmp_fname));
  // NOTE: dirname must be done last, as it is semi-destructive!

  if (dirName.empty() || dirName == ".") {
    // No directory specified - so use current.
    dirName = PathName::GetCurrentDirectory();
  }
}

PathName::PathName(const FileName &file_name)
    : PathName(file_name.to_string()) {
}
// End PathName constructor //


// Summary -----------------------------------------------------------------
//
// Member function FullName.
//	Return the full path name, which will be of the form :-
//		/dir1/dir2/fname
//	The path name will be stored in a static buffer, and so will
//	be overwritten by subsequent calls.
//
// End ---------------------------------------------------------------------
std::string PathName::FullName() const {
  std::stringstream ss;
  if (fileExists) {
    ss << dirName << "/" << fileName;
  } else {
    ss << "**Non-existent:" << fileName << "**";
  }
  return ss.str();
}
/* End Member function FullName */

/**
 * Find the current working directory.
 * @return Current directory.
 */
std::string PathName::GetCurrentDirectory() {
  char dname[PATH_MAX + 1];
  getcwd(dname, PATH_MAX);
  return std::string(dname);
}

/****************************************************************************/
/* $Log$
 * Revision 1.1  1996/05/07 14:29:37  njt
 * Initial revision
 *
 * Revision 1.1  91/07/06  23:51:02  njt
 * Added assignment operator= for FileName & PathName classes.
 * 
 * Revision 1.0  91/03/02  00:00:00  njt
 * Initial revision
*****************************************************************************/
