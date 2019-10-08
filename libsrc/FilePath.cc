#include "FilePath.h"

#include <sstream>
#include <string>

#include "fileutil.h"


FilePath::FilePath(const char *file_path)
    : FilePath(std::string(file_path)) {
}

FilePath::FilePath(const std::string &file_path) {
  // Split file name into components

  fileName = FileUtils::basename(file_path);
  dirName = FileUtils::dirname(file_path);

  if (dirName.empty() || dirName == ".") {
    // No directory specified - so use current.
    dirName = FileUtils::GetCurrentDirectory();
  }

  fileExists = FileUtils::IsFileReadable(file_path);
}
// End FilePath constructor //


/**
 * Member function FullName
 * @return Return the full path name, which will be of the form /path/to/filename
 */
std::string FilePath::FullName() const {
  std::stringstream ss;
  if (fileExists) {
	ss << dirName << FileUtils::DirSeparator() << fileName;
  } else {
    ss << "**Non-existent:" << fileName << "**";
  }
  return ss.str();
}
/* End Member function FullName */

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
