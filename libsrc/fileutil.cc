#include <ctime>
#include <iostream>
#include <string>
#include <sys/stat.h> // For stat function.

#include "fileutil.h"

// #define EXTRA_DEBUG

#if defined(_WIN32)
// Windows
#include <direct.h> // For getcwd function.
#include <io.h>     // For access function.
constexpr int PATH_MAX = 260;
#ifndef R_OK
constexpr int R_OK = 4;
#endif
#else
// Linux / UNIX / MacOS
#include <climits> // For PATH_MAX
#include <unistd.h> // For access and getcwd functions.
#endif

bool FileUtils::IsFileReadable(const std::string& file_path)
{
  return access(file_path.c_str(), R_OK) == 0;
}

long FileUtils::FileSize(const std::string& file_path)
{
  const auto  func_name = "FileSize";
  struct stat stats {
  };

  if (stat(file_path.c_str(), &stats) == 0) {
    return stats.st_size;
  }
  else {
    std::cerr << __FILE__ << "::" << func_name << ": Bad return from stat function on file " << file_path << std::endl;
    return -1;
  }
}

time_t FileUtils::FileCreationTimestamp(const std::string& file_path)
{
  const auto  func_name = "FileCreationTimestamp";
  struct stat stats {
  };

  if (stat(file_path.c_str(), &stats) == 0) {
    return stats.st_mtime;
  }
  else {
    std::cerr << __FILE__ << "::" << func_name << ": Bad return from stat function on file " << file_path << std::endl;
    return 0;
  }
}

std::string FileUtils::GetModificationDate(const std::string& file_path)
{
  time_t timestamp = FileUtils::FileCreationTimestamp(file_path);

  struct tm time {
  };
  char time_str[26];

#ifdef _MSC_VER
  localtime_s(&time, &timestamp);
  asctime_s(time_str, sizeof time_str, &time);
#else
  localtime_r(&timestamp, &time);
  asctime_r(&time, time_str);
#endif

  // Clean any non-printable characters.
  for (size_t i = 0; i < sizeof time_str; i++) {
    if (!isprint(time_str[i])) {
      time_str[i] = ' ';
    }
  }
  auto modTime = std::string(time_str);
#ifdef EXTRA_DEBUG
  std::cerr << "[" << modTime << "]"
            << " c='" << modTime[modTime.length() - 1] << "'"
            << " len = " << modTime.length() << std::endl;
#endif
  return modTime;
}
// End Member function ModificationDate

// Based on https://stackoverflow.com/a/43283887/282326
std::string FileUtils::basename(const std::string& file_path)
{
  if (file_path.empty()) {
    return {};
  }

  auto len   = file_path.length();
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

std::string FileUtils::dirname(const std::string& file_path)
{
  if (file_path.empty()) {
    return ".";
  }

  const auto len   = file_path.length();
  const auto index = file_path.find_last_of("/\\");

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
std::string FileUtils::GetCurrentDirectory()
{
  char dir_name[PATH_MAX + 1];
  getcwd(dir_name, PATH_MAX);
  return std::string(dir_name);
}
