#ifndef _FILEUTIL_H
#define _FILEUTIL_H

#include <cstring>

/**
 * Standalone, low-level file utilities.
 */
class FileUtils {
public:
  /**
   * Function: IsFileReadable
   * @param file_path - The file to be inspected.
   * @return Return TRUE if specified file exists and is readable.
   */
  static bool IsFileReadable(const std::string &file_path);

  /**
   * Function: FileSize
   * @param file_path - The file to be inspected.
   * @return Return size of specified file (in bytes)
   */
  static long FileSize(const std::string &file_path);

  /**
   * Function: FileCreationTimestamp
   * @param file_path - The file to be inspected.
   * @return Return creation timestamp of the specified file.
   */
  static time_t FileCreationTimestamp(const std::string &file_path);
};

#endif // _FILEUTIL_H
