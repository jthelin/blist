#include <climits>  // For PATH_MAX
#include <cstdlib>    // For PATH_MAX
#include <iostream>
#include <string>
#include <sys/stat.h> // For stat function.
#include <unistd.h>  // For access and getcwd functions.

#include "fileutil.h"

#ifndef R_OK
#define R_OK 4
#endif

bool FileUtils::IsFileReadable(const std::string &file_path) {
  return access(file_path.c_str(), R_OK) == 0;
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

// Based on https://stackoverflow.com/a/43283887/282326
std::string FileUtils::basename(const std::string &file_path)
{
  if (file_path.empty()) {
    return {};
  }

  auto len = file_path.length();
  auto index = file_path.find_last_of("/\\");

  if (index == std::string::npos) {
    return file_path;
  }

  if (index + 1 >= len) {

    len--;
    index = file_path.substr(0, len).find_last_of("/\\");

    if (len == 0) {
      return file_path;
    }

    if (index == 0) {
      return file_path.substr(1, len - 1);
    }

    if (index == std::string::npos) {
      return file_path.substr(0, len);
    }

    return file_path.substr(index + 1, len - index - 1);
  }

  return file_path.substr(index + 1, len - index);
}

std::string FileUtils::dirname(const std::string &file_path)
{
  if (file_path.empty()) {
    return ".";
  }

  auto len = file_path.length();
  auto index = file_path.find_last_of("/\\");

  if (index == std::string::npos) {
    return ".";
  }

  if (index == 0) {
    return file_path;
  }

  if (index + 1 == len) {
  	// Omit trailing '/' in directory names.
    return file_path.substr(0, index);
  }

  return file_path.substr(0, index);
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
