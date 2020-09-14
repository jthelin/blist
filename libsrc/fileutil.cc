#include "fileutil.h"

// #define EXTRA_DEBUG

#if defined(EXTRA_DEBUG)
#include <iostream>
#endif

std::string FileUtils::GetModificationDate(const std::filesystem::path& file_path)
{
  time_t timestamp = FileUtils::FileCreationTimestamp(file_path);

  struct tm time {
  };
  char time_str[26];

#if defined(_MSC_VER)
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
#if defined(EXTRA_DEBUG)
  std::cerr << "[" << modTime << "]"
            << " c='" << modTime[modTime.size() - 1] << "'"
            << " len = " << modTime.size() << std::endl;
#endif
  return std::move(modTime);
}
// End Member function ModificationDate
