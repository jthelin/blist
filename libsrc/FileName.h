#pragma title( "FileName class declaration" )

#ifndef FILENAME_h
#define FILENAME_h

// Contents ----------------------------------------------------------------
//
//	Contains the class declaration for the FileName class
//
// End ---------------------------------------------------------------------


// Interface Dependencies --------------------------------------------------
#include "Boolean.h"
#include "sstring.h"
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
//		[ NOTE: This is just the terminal name, e.g. fname.ext ]
//	fileExists
//		TRUE if a file of this name exists in the file system.
//
// End ---------------------------------------------------------------------
class FileName
{
protected:
	string		fileName;
	BOOL		fileExists;
public:
			FileName ( const char filename[] );
	virtual		~FileName ( void )  { };

	FileName&	operator = ( const FileName& other );

	virtual		operator const char * ( void ) const
			{ return (const char *) fileName; }
	BOOL		Exists ( void ) const
			{ return fileExists; };
protected:
			FileName ( void ) 
			:	fileName( "" )
			{	fileExists = FALSE;
				/* No access */ };
			FileName ( const FileName& other )
			:	fileName( other.fileName ),
				fileExists( other.fileExists )
			{ /* No access */ };
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

class PathName : public FileName
{
protected:
	string         	dirName;
public:
				PathName ( const char filename[] );
	virtual			~PathName ( void )
				{ };

	PathName&		operator = ( const PathName& other );

	virtual 		operator const char * ( void )  const
				{ return this->FullName(); };
	virtual const char *    DirName ( void )  const
				{ return (const char *) dirName; };
	virtual const char *    FName ( void )  const
				{ return (const char *) fileName; };
	virtual const char *    FullName ( void )  const;
protected:
				PathName ( void )
				: FileName(), dirName( "" )
				{ /* No access */ };
//				PathName ( const PathName& other )
//				: FileName( other ), dirName( other.dirName )
//				{ /* No access */ };
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
22-Apr-96	NJT	v1.1 - Initial UNIX version under SCCS control.
******************************************************************************/

#endif /* ifndef FILENAME_h */
/* EOF */
