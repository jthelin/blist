#include "fileutil.h"

// #define EXTRA_DEBUG

#if defined(EXTRA_DEBUG)
#include <iostream>
#endif

std::string FileUtils::GetModificationDate(const std::filesystem::path& file_path)
{
  auto ftime = FileCreationTimestamp(file_path);

  time_t    timestamp = decltype(ftime)::clock::to_time_t(ftime);
  struct tm time {};
  char      time_str[26];

#if defined(_MSC_VER)
  localtime_s(&time, &timestamp);
  asctime_s(time_str, sizeof time_str, &time);
#else
  localtime_r(&timestamp, &time);
  asctime_r(&time, time_str);
#endif

  // Clean any non-printable characters.
  for (size_t i = 0; i < sizeof time_str; i++) {
    if (time_str[i] == '\0') {
      break;
    }
    if (!isprint(time_str[i])) {
      time_str[i] = ' ';
    }
  }

  auto modTime = std::string(time_str, strnlen(time_str, sizeof time_str));
#if defined(EXTRA_DEBUG)
  std::cerr << "[" << modTime << "]" << std::endl;
#endif
  return modTime;
}
// End Member function ModificationDate
