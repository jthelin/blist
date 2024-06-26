#pragma once

#include <chrono>
#include <ctime>
#include <filesystem>
#include <string>

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
  static bool IsFileReadable(const std::filesystem::path& file_path)
  {
    if (!std::filesystem::exists(file_path)) {
      return false;
    }
    auto status = std::filesystem::status(file_path);
    return (status.permissions() & std::filesystem::perms::owner_read) != std::filesystem::perms::none;
  }

  /**
   * Function: FileCreationTimestamp
   * @param file_path - The file to be inspected.
   * @return Return creation timestamp of the specified file.
   */
  static std::filesystem::file_time_type FileCreationTimestamp(const std::filesystem::path& file_path)
  {
    return std::filesystem::last_write_time(file_path);
  }

  /**
   * Get a printable string containing the modification date of a file.
   * @param file_path - The file to be inspected.
   * @return Return a string containing the modification date of a file.
   */
  static std::string GetModificationDate(const std::filesystem::path& file_path);

  static std::string basename(const std::filesystem::path& file_path)
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
  static std::string dirname(const std::filesystem::path& file_path)
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
};
