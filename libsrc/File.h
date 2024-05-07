#pragma once

// Contents ----------------------------------------------------------------
//
//    Contains the class declaration for the File class
//
// End ---------------------------------------------------------------------

#include <filesystem>
#include <iosfwd>
#include <string>
#include <vector>

/*!
 * An object representing a DOS (text) file, including its contents.
 */
class File {
public:
  /*!
   * Constructor - Creates an object representing the file with the specified (path) name.
   * @param file_path - The location of the file on disk.
   * @param log_failures - If false. then no failure or warning messages will be logged if the file does not exist.
   */
  explicit File(const std::string& file_path, bool log_failures = true);

  /*!
   * Destructor for File object
   */
  virtual ~File();

  /*! ModificationDate - Return a string containing the modification date of a File. */
  [[nodiscard]] std::string ModificationDate() const;

  /*! FileSize - Return a File's size in bytes. */
  [[nodiscard]] size_t FileSize() const { return std::filesystem::file_size(_file); }

  /*! FileInfo - Return list of strings containing the file info details. */
  [[nodiscard]] std::vector<std::string> FileInfo() const;

  /*! Return true if this file exists on disk. */
  [[nodiscard]] bool Exists() const
  {
    return std::filesystem::exists(_file) && std::filesystem::is_regular_file(_file);
  }

  /*! Return the full path name of this file. */
  [[nodiscard]] std::string FullName() const
  {
    return std::filesystem::absolute(_file).lexically_normal().generic_string();
  }

  /*! PrintTo - Outputs the contents of the file to the specified output stream. */
  virtual void PrintTo(std::ostream& s);

  /*! Puts the File contents out to the specified output stream. */
  friend std::ostream& operator<<(std::ostream& s, File f)
  {
    f.PrintTo(s);
    return s;
  }

private:
  std::filesystem::path _file;
};

/* Original RCS change records from DOS version: */
/*****************************************************************************
 * $Log$
 * Revision 1.1  1996/05/07 14:29:35  njt
 * Initial revision
 *
 * Revision 2.2  91/04/12  00:00:00  njt
 * Added the functions more() and next() to FileIterator, to improve
 * readability when this iterator is used.
 * Added function printOn(..) to the File class, to allow better use of
 * printing facilities with derived classes.
 * Also rearranged the file so that the inline functions are separate, and
 * not cluttering up the class definitions.
 * 
 * Revision 2.1  91/03/22  00:00:00  njt
 * Added the FileIterator class.
 * Revision 2.0  91/03/02            njt
 * Completely rewritten using the PathName class, and now providing a much
 * more general purpose interface to the file contents using record-level
 * access.
 * Revision 1.1  91/02/09  17:49:41  njt
 * Initial version
 *
 ****************************************************************************/

/******************************************************************************
 Change History
 ==============

Date          | Name  | Description
--------------+-------+-------------------------------------------------------
23-Apr-96       NJT     v1.1 - Initial UNIX version under SCCS control.
02-May-96       NJT     v1.2 - Removed all file iterator functionality from class File.
                               Class FileIterator is not working properly yet.
******************************************************************************/
