// Contents ----------------------------------------------------------------
//
//	Contains the implementation for the FileName class
//
// Required libraries:  -lgen
//
// End ---------------------------------------------------------------------

// Interface Declarations --------------------------------------------------
#include "FileName.h"
// End Interface Declarations ----------------------------------------------

// Implementation Dependencies ----------------------------------------------
#include <unistd.h>	// For getcwd
#include <limits.h>	// For PATH_MAX
#include "sstring.h"	// For class string
extern "C" {
#include <libgen.h>	// For basename / dirname
#include "fileutil.h"
}
// End Implementation Dependencies -------------------------------------------


// Summary -----------------------------------------------------------------
//
// Constructor for FileName object
//	Initialises the object data.
//
// Parameters
//	fname
//		The filename we are to use to locate this file.
//
// End ---------------------------------------------------------------------
FileName::FileName ( const char fname[] )
  :  fileName ( fname )
{
	fileExists = IsFileReadable( fname );
}
// End FileName constructor //


// Summary -----------------------------------------------------------------
//
// Assignment operator for FileName object (operator =).
//	Initialises the object data.
//
// Parameters
//	other
//		The other FileName object to be assigned to this one.
//
// End ---------------------------------------------------------------------
FileName&    FileName::operator = ( const FileName& other )
{
	if ( *this != other )
	{
		fileExists = other.fileExists;
		fileName = other.fileName;
	}

	return *this;
};
// End Member Function  operator = //


// Summary -----------------------------------------------------------------
//
// Constructor for PathName object.
//	Initialises the object data.
//
// Parameters
//	fname
//		The filename we are to use to locate this file.
//
// End ---------------------------------------------------------------------
PathName::PathName ( const char fname[] )
  :  FileName ( fname ), dirName ( "." )
{
	if (fileExists)
	{
		// Split file name into components
		string tmpfname( fname );
		fileName = basename( (char*) tmpfname );
		dirName  = dirname(  (char*) tmpfname );
		// NOTE: dirname must be done last, as it is semi-descructive!

		if ( strcmp(dirName,".") == 0 )
		{
			// No directory specified - so use current.
			char	dname[PATH_MAX+1];
			getcwd(dname,PATH_MAX);
			dirName = dname;  /* Create directory name string */
		}
	}
	else
	{
		// File does not exist
		// dirName is already initialised to null string
	}
}
// End PathName constructor //


// Summary -----------------------------------------------------------------
//
// Member function FullName.
//	Return the full path name, which will be of the form :-
//		/dir1/dir2/fname
//	The path name will be stored in a static buffer, and so will
//	be overwritten by subsequent calls.
//
// End ---------------------------------------------------------------------
const char * PathName::FullName ( void )  const
{
	static  char  path[PATH_MAX+1];

        if (fileExists) {
		strcpy(path,dirName);
		strcat(path,"/");
		strcat(path,fileName);
	}
	else
	{
		strcpy(path,"**Non-existant:");
		strncat(path,fileName,(PATH_MAX-strlen(path)));
		strncat(path,"**",(PATH_MAX-strlen(path)));
	}

	return path;
}
/* End Member function FullName */


// Summary -----------------------------------------------------------------
//
// Assignment operator for PathName object (operator =).
//
// Parameters
//	other
//		The other PathName object to be assigned to this one.
//
// End ---------------------------------------------------------------------
PathName&    PathName::operator = ( const PathName& other )
{
	if ( *this != other )
	{
		fileExists = other.fileExists;
		fileName = other.fileName;
		dirName = other.dirName;
	}

	return *this;
};
/* End Member Function  operator = */



#ifdef TEST
//     ****

// **********************************
// main function for testing purposes
// **********************************

void main ( int argc, char *argv[] )
{
	FileName *      f    = new FileName("FileName.C");  // This file !
	FileName *      none = new FileName("nofile.non");  // Non-existant file

	cout << "Start FileName test" << endl;
	cout << endl;

	cout << FileName("FileName.h") << endl;
	cout << "f : " << *f << endl;
	cout << "f: Exists = " << f->Exists() << endl;

	cout << "none : " << *none << endl;
	cout << "none: Exists = " << none->Exists() << endl;

	f = new PathName( *f );
	cout << "path f : " << *f << endl;
	cout << "path f: Exists = " << f->Exists() << endl;

	cout << endl;

	if (argc > 1) {
		cout << "User supplied files" << endl;

		for ( int i = 1; i<argc; i++ )
		{
			cout << "arg " << i << " : " << argv[i] << endl;

			f = new PathName ( argv[i] );
			cout << "path : " << *f << endl;
			cout << "path : Exists = " << f->Exists() << endl;
		}
	}

	cout << endl;
	cout << "End FileName test" << endl;
}
#endif /* TEST */



/****************************************************************************/
/* $Log$
/* Revision 1.1  1996/05/07 14:29:37  njt
/* Initial revision
/*
 * Revision 1.1  91/07/06  23:51:02  njt
 * Added assignment operator= for FileName & PathName classes.
 * 
 * Revision 1.0  91/03/02  00:00:00  njt
 * Initial revision
*****************************************************************************/
