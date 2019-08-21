#include "FilePath.h"

#include <sstream>
#include <string>
#include <unistd.h>  // For getcwd
#include <climits>  // For PATH_MAX
#include <libgen.h>  // For basename / dirname
#include "fileutil.h"


FilePath::FilePath(const std::string &path)
    : FilePath(path.c_str()) {
}

FilePath::FilePath(const char *path) {
  // Split file name into components

  char *tmp_fname = ((char *) path);
  fileName = std::string(basename(tmp_fname));
  dirName = std::string(dirname(tmp_fname));
  // NOTE: dirname must be done last, as it is semi-destructive!

  if (dirName.empty() || dirName == ".") {
    // No directory specified - so use current.
    dirName = FilePath::GetCurrentDirectory();
  }

  fileExists = IsFileReadable(path);
}
// End FilePath constructor //


/**
 * Member function FullName
 * @return Return the full path name, which will be of the form /path/to/filename
 */
std::string FilePath::FullName() const {
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
std::string FilePath::GetCurrentDirectory() {
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
 * Added assignment operator= for FileName & FilePath classes.
 * 
 * Revision 1.0  91/03/02  00:00:00  njt
 * Initial revision
*****************************************************************************/
