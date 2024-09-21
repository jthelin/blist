#include "fileutil.h"

#include <array>
#include <chrono>
#include <cstring>
#include <ctime>
#include <stdexcept>

// #define EXTRA_DEBUG

#if defined(EXTRA_DEBUG)
#include <iostream>
#endif

bool FileUtils::IsFileReadable(const std::filesystem::path& file_path)
{
  if (!std::filesystem::exists(file_path)) {
    return false;
  }
  auto status = std::filesystem::status(file_path);
  return (status.permissions() & std::filesystem::perms::owner_read) != std::filesystem::perms::none;
}

std::filesystem::file_time_type FileUtils::FileCreationTimestamp(const std::filesystem::path& file_path)
{
  if (!std::filesystem::exists(file_path)) {
    throw std::invalid_argument("File not found: " + file_path.lexically_normal().string());
  }
  return std::filesystem::last_write_time(file_path);
}

std::string FileUtils::GetModificationDate(const std::filesystem::path& file_path)
{
  auto ftime = FileCreationTimestamp(file_path);

  time_t timestamp;
#if defined(__APPLE__)
  static_assert(std::is_same_v<decltype(ftime)::clock, std::filesystem::_FilesystemClock>);
  timestamp = decltype(ftime)::clock::to_time_t(ftime);
#else
  auto time_point = std::chrono::system_clock::time_point{ftime.time_since_epoch()};
  timestamp       = std::chrono::system_clock::to_time_t(time_point);
#endif

  struct tm time         = {};
  auto      time_str_raw = std::array<char, 26>();

#if defined(_MSC_VER)
  localtime_s(&time, &timestamp);
  asctime_s(time_str_raw.data(), time_str_raw.size(), &time);
#else
  localtime_r(&timestamp, &time);
  asctime_r(&time, time_str_raw.data());
#endif

  // Clean any non-printable characters.
  for (size_t i = 0; i < time_str_raw.size() && time_str_raw[i] != '\0'; i++) {
    if (!isprint(time_str_raw[i])) {
      time_str_raw[i] = ' ';
    }
  }

  auto modTime = std::string(time_str_raw.data(), strnlen(time_str_raw.data(), time_str_raw.size()));
#if defined(EXTRA_DEBUG)
  std::cerr << "[" << modTime << "]" << std::endl;
#endif
  return modTime;
}
// End Member function ModificationDate

std::string FileUtils::basename(const std::filesystem::path& file_path)
{
  std::filesystem::path file_name;
  if (!file_path.empty()) {
    file_name = file_path.filename();
  }
  if (file_name.empty()) {
    return "";
  }
  return file_name.lexically_normal().generic_string();
}
std::string FileUtils::dirname(const std::filesystem::path& file_path)
{
  std::filesystem::path dir_path;
  if (!file_path.empty()) {
    dir_path = std::filesystem::path{file_path}.remove_filename();
  }
  if (dir_path.empty()) {
    return ".";
  }
  return dir_path.lexically_normal().generic_string();
}
