#ifndef FILE_PATH_h
#define FILE_PATH_h

#include <string>

#pragma title( "FilePath class declaration" )
/**
 * Class FilePath
 * ==============
 * An object representing a file system path.
 */
class FilePath {
protected:
  bool fileExists;
  std::string fileName;
  std::string dirName;
public:
  /**
   * Constructor for FilePath object.
   * @param path - The path location for this file.
   */
  explicit FilePath(const std::string &path);

  /**
   * Constructor for FilePath object.
   * @param path - The path location for this file.
   */
  explicit FilePath(const char *file_name);

  /**
   * Copy constructor for FilePath object.
   */
  FilePath(const FilePath &other) = default;

  /**
   * Destructor function for FilePath object.
   */
  ~FilePath() = default;

  FilePath &operator=(const FilePath &other) = delete;
  FilePath &operator=(const FilePath *other) = delete;

  /**
   * @return Returns true if this file path exists in the file system.
   */
  bool Exists() const { return fileExists; };

  /**
   * @return Return the directory name (including drive, if applicable) for this file.
   */
  std::string DirName() const { return dirName; };

  /**
   * @return Return the terminal file name of this file, including file extension (if applicable).
   */
  std::string FName() const { return fileName; };

  /**
   * @return Return the full path name of this file.
   */
  std::string FullName() const;

  std::string to_string() const { return this->FullName(); };

  /**
   * Find the current working directory.
   * @return Current directory.
   */
  static std::string GetCurrentDirectory();

  friend std::ostream &operator<<(std::ostream &s, const FilePath &path_name) {
    s << path_name.FullName();
    return s;
  };
};

#endif // FILE_PATH_h
