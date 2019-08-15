#ifndef FILENAME_h
#define FILENAME_h

#pragma title( "FileName class declaration" )

#include <string>

#pragma subtitle( "Class: FileName" )

// Description -------------------------------------------------------------
//
// class FileName
// ==============
//
//	An object representing a DOS file name.
//
// Constructor: FileName
//	Creates a File object representing the file with the specified name.
//	Sets the file exists flag appropriately.
//
// Destructor: ~FileName
//
// Member functions:
//	Exists
//		Returns true if this file exists in the file system.
//	operator const char *
//		Return the file name of this file.
//
// Stream output function
//	None - use predefined stream output by converting to char *
//
// Inherited Members
//	None.
//
// Private Members
//	None
//
// Protected Members
//	fileName
//		The name of this file.
//		[ NOTE: This is just the terminal name, e.g. filename.ext ]
//	fileExists
//		TRUE if a file of this name exists in the file system.
//
// End ---------------------------------------------------------------------
class FileName {
protected:
  bool fileExists;
  std::string fileName;
public:
  explicit FileName(const std::string &filename);

  explicit FileName(const char *filename);

  FileName(const FileName &other) = default;

  virtual ~FileName() = default;

  FileName &operator=(const FileName &other) = default;

  virtual std::string to_string() const { return this->fileName; };

  bool Exists() const { return fileExists; };

  friend std::ostream &operator<<(std::ostream &s, const FileName &f) {
    s << f.fileName;
    return s;
  };

protected:
  FileName()
      : fileName("") {
    fileExists = false;
    /* No access */ };

};


#pragma subtitle( "Class: PathName" )

/* Description *************************************************************
//
// class PathName
// ==============
//
//	An object representing a full path name.
//
// Constructor: PathName
//	Creates an object representing the DOS path file for this file.
//
// Destructor: ~PathName
//
// Member functions:
//	DirName
//		Return the directory (& drive) name for this file.
//	FullName
//		Return the full path name of this file.
//	FName
//		Return the terminal file name for this file.
//	operator const char *
//		Return the full file name of this file.
//
// Stream output functions:
//	None - use predefined stream output by converting to char *
//
// Inherited Members:
//	Exists	- from FileName.
//
// Private Members:
//	None
//
// Protected Members:
//	dirName
//		The name of the directory (& drive) for this file.
//		It is of the form :-
//			/dir1/dir2/
//
** End ********************************************************************/

class PathName : public FileName {
protected:
  std::string dirName;
public:
  explicit PathName(const std::string &path);

  explicit PathName(const FileName &file_name);

  PathName(const PathName &other) = default;

  ~PathName() override = default;

  PathName &operator=(const PathName &other) = default;

  PathName &operator=(const PathName *other) {
    this->operator=(*other);
    return *this;
  };

  std::string to_string() const override { return this->FullName(); };

  virtual std::string DirName() const { return dirName; };

  virtual std::string FName() const { return fileName; };

  virtual std::string FullName() const;

  static std::string GetCurrentDirectory();

  friend std::ostream &operator<<(std::ostream &s, const PathName &path_name) {
    s << path_name.FullName();
    return s;
  };

protected:
  PathName()
      : FileName(), dirName(".") { /* No access */ };
};


/* Original RCS change records from DOS version: */
/******************************************************************************
 * $Log$
 * Revision 1.1  1996/05/07 14:29:35  njt
 * Initial revision
 *
 * Revision 1.1  91/07/06  23:44:10  ROOT_DOS
 * Separated out inline functions from class definition.
 * Added assignment operator= functions for FileName & PathName classes.
 * Added non-visible basic copy & null constructors to FileName & PathName
 * classes to help detect incorrect initalisations & copies.
 * Revision 1.0  91/03/02  00:00:00  njt
 * Initial revision
*****************************************************************************/

/******************************************************************************
 Change History
 ==============

Date          | Name  | Description
--------------+-------+-------------------------------------------------------
22-Apr-96       NJT     v1.1 - Initial UNIX version under SCCS control.
******************************************************************************/

#endif /* ifndef FILENAME_h */
