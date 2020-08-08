#ifndef FILE_PATH_h
#define FILE_PATH_h

#include <string>

/**
 * Class FilePath
 * ==============
 * An object representing a file system path.
 */
class FilePath {
protected:
  bool        fileExists;
  std::string fileName;
  std::string dirName;

public:
  /**
   * Constructor for FilePath object.
   * @param file_path - The path location for this file.
   */
  explicit FilePath(const std::string& file_path);

  /**
   * Constructor for FilePath object.
   * @param file_path - The path location for this file.
   */
  explicit FilePath(const char* file_path);

  // Copy constructors for FilePath object.
  FilePath(const FilePath&) = default;
  FilePath& operator=(const FilePath&) = default;
  // Move constructors for FilePath object.
  FilePath(FilePath&&) = default;
  FilePath& operator=(FilePath&&) = default;

  /**
   * Destructor function for FilePath object.
   */
  virtual ~FilePath() = default;

  /**
   * @return Returns true if this file path exists in the file system.
   */
  [[nodiscard]] bool Exists() const { return fileExists; };

  /**
   * @return Return the directory name (including drive, if applicable) for this file.
   */
  [[nodiscard]] std::string DirName() const { return dirName; };

  /**
   * @return Return the terminal file name of this file, including file extension (if applicable).
   */
  [[nodiscard]] std::string FName() const { return fileName; };

  /**
   * @return Return the full path name of this file.
   */
  [[nodiscard]] std::string FullName() const;

  [[nodiscard]] std::string to_string() const { return this->FullName(); };

  friend std::ostream& operator<<(std::ostream& s, const FilePath& path_name)
  {
    s << path_name.FullName();
    return s;
  };
};

#endif // FILE_PATH_h
