#include "fileutil.h"

// #define EXTRA_DEBUG

std::string FileUtils::GetModificationDate(const std::filesystem::path& file_path)
{
  std::time_t timestamp = FileUtils::FileCreationTimestamp(file_path);

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
