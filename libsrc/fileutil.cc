#include <climits>  // For PATH_MAX
#include <cstdlib>    // For PATH_MAX
// #include <direct.h>   // For _getcwd
#include <iostream>
#include <string>
#include <sys/stat.h> // For stat function.
#include <unistd.h>  // For access function.
#include <unistd.h>  // For getcwd

#include "fileutil.h"

bool FileUtils::IsFileReadable(const std::string &file_path) {
  return access(file_path.c_str(), F_OK | R_OK) == 0;
}

long FileUtils::FileSize(const std::string &file_path) {
  auto func_name = "FileSize";
  struct stat stats{};

  if (stat(file_path.c_str(), &stats) == 0) {
    return stats.st_size;
  } else {
    std::cerr << __FILE__ << "::" << func_name
              << ": Bad return from stat function on file " << file_path
              << std::endl;
    return -1;
  }
}

time_t FileUtils::FileCreationTimestamp(const std::string &file_path) {
  auto func_name = "FileCreationTimestamp";
  struct stat stats{};

  if (stat(file_path.c_str(), &stats) == 0) {
    return stats.st_mtime;
  } else {
    std::cerr << __FILE__ << "::" << func_name
              << ": Bad return from stat function on file " << file_path
              << std::endl;
    return 0;
  }
}

/**
 * Find the current working directory.
 * @return Current directory.
 */
std::string FileUtils::GetCurrentDirectory() {
  char dir_name[PATH_MAX + 1];
  getcwd(dir_name, PATH_MAX);
  return std::string(dir_name);
}
