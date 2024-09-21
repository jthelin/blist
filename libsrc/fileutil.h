#pragma once

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
  static bool IsFileReadable(const std::filesystem::path& file_path);

  /**
   * Function: FileCreationTimestamp
   * @param file_path - The file to be inspected.
   * @return Return creation timestamp of the specified file.
   */
  static std::filesystem::file_time_type FileCreationTimestamp(const std::filesystem::path& file_path);

  /**
   * Get a printable string containing the modification date of a file.
   * @param file_path - The file to be inspected.
   * @return Return a string containing the modification date of a file.
   */
  static std::string GetModificationDate(const std::filesystem::path& file_path);

  static std::string basename(const std::filesystem::path& file_path);
  static std::string dirname(const std::filesystem::path& file_path);
};
