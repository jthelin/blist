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
#include <string>
#include <unistd.h>  // For getcwd
#include <climits>  // For PATH_MAX
#include "fileutil.h"
#include <libgen.h>  // For basename / dirname
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
FileName::FileName(const std::string& fname)
    : fileName(fname) {
  fileExists = IsFileReadable(fname);
}
// End FileName constructor //


// Summary -----------------------------------------------------------------
//
// Constructor for PathName object.
//	Initialises the object data.
//
// Parameters
//	path
//		The filename we are to use to locate this file.
//
// End ---------------------------------------------------------------------
PathName::PathName(const std::string &path)
    : FileName(path), dirName(".") {
  if (fileExists) {
    // Split file name into components
    // int pos = path.last_index_of()
    std::string tmpfname = path;
    fileName = basename((char *) tmpfname.c_str());
    dirName = dirname((char *) tmpfname.c_str());
    // NOTE: dirname must be done last, as it is semi-destructive!

    if (dirName == ".") {
      // No directory specified - so use current.
      char dname[PATH_MAX + 1];
      getcwd(dname, PATH_MAX);
      dirName = dname;  /* Create directory name string */
    }
  } else {
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
std::string PathName::FullName() const {
  static char path[PATH_MAX + 1];

  if (fileExists) {
    strcpy(path, dirName.c_str());
    strcat(path, "/");
    strcat(path, fileName.c_str());
  } else {
    strcpy(path, "**Non-existent:");
    strncat(path, fileName.c_str(), (PATH_MAX - strlen(path)));
    strncat(path, "**", (PATH_MAX - strlen(path)));
  }

  return path;
}
/* End Member function FullName */


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
 * Revision 1.1  1996/05/07 14:29:37  njt
 * Initial revision
 *
 * Revision 1.1  91/07/06  23:51:02  njt
 * Added assignment operator= for FileName & PathName classes.
 * 
 * Revision 1.0  91/03/02  00:00:00  njt
 * Initial revision
*****************************************************************************/
