#pragma title( "FileName class declaration" )

#ifndef FILENAME_h
#define FILENAME_h

// Contents ----------------------------------------------------------------
//
//	Contains the class declaration for the FileName class
//
// End ---------------------------------------------------------------------


// Interface Dependencies --------------------------------------------------
#include <string>
// End Interface Dependencies ----------------------------------------------

// Implementation Dependencies ---------------------------------------------
// End Implementation Dependencies -----------------------------------------

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
  std::string fileName;
  bool fileExists;
public:
  explicit FileName(const std::string& filename);

  virtual ~FileName() = default;;

  FileName &operator=(const FileName &other) = default;

  virtual explicit operator std::string() const { return fileName; }

  bool Exists() const { return fileExists; };
protected:
  FileName()
      : fileName("") {
    fileExists = false;
    /* No access */ };

  FileName(const FileName &other) = default;
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

  ~PathName() override = default;

  PathName &operator=(const PathName &other) = default;

  explicit operator std::string() const override { return this->FullName(); };

  virtual std::string DirName() const { return dirName; };

  virtual std::string FName() const { return fileName; };

  virtual std::string FullName() const;

protected:
  PathName()
      : FileName(), dirName("") { /* No access */ };
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
