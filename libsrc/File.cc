// Contents ----------------------------------------------------------------
//
//	Contains the implementation for the File class
//
// End ---------------------------------------------------------------------

// Interface Declarations --------------------------------------------------
#include "File.h"
// End Interface Declarations ----------------------------------------------

// Implementation Dependencies ----------------------------------------------
#include <assert.h>
#include <iostream.h>
#include <fstream.h>
#include <string.h>
#include "utildbug.h"
#include "filter.h"
extern "C" {
#include "fileutil.h"
}
// End Implementation Dependencies -------------------------------------------


// Summary -----------------------------------------------------------------
//
// Constructor for File object
//	No failure or warning messages will be logged if the file does not
//	exist if log_failures is false.
//
// End ---------------------------------------------------------------------
File::File ( const char fname[], BOOL log_failures )
: PathName( fname )
{
	TraceEntryExit	t( "File", "<constructor>" );

	if (!Exists())
	{
		// File does not exist
		if (log_failures)
		{
			cerr	<< "**** ERROR :  "
				<< "File " << fname << " does not exist"
				<< endl;
		}
	}
}
// End File constructor //


// Summary -----------------------------------------------------------------
//
// Destructor for File object
//	Closes the input stream if it is open.
//
// End ---------------------------------------------------------------------
File::~File ( )
{
	TraceEntryExit t( "File", "<destructor>" );
}
// End File Destructor //


// Summary -----------------------------------------------------------------
//
// Member Function ModificationDate
//	Return a pointer to a string containing the modification date of a File.
//
// End ---------------------------------------------------------------------
const char *	File::ModificationDate( )
{
	static char szModnDate[] = "";  /* HACK! */

	return szModnDate;
}
// End Member function ModificationDate


// Summary -----------------------------------------------------------------
//
// Member Function FileSize
//	Return a File's size in bytes.
//
// End ---------------------------------------------------------------------
long  File::FileSize( )
{
	return ::FileSize( this->FullName() );
}
// End Member function Size


// Summary -----------------------------------------------------------------
//
// Member Function FileInfo
//	Return a (static) string array of file info details
//
// End ---------------------------------------------------------------------
char**  File::FileInfo( )
{
	static char finfo[4][300];
	char fsize[20];

	strcpy(finfo[0], "File name: " );
	strcat(finfo[0], this->FullName() );

	strcpy(finfo[1], "Last modified: " );
	strcat(finfo[1], this->ModificationDate() );

	sprintf( fsize, "%ld", this->FileSize() );
	strcpy(finfo[2], "File size (bytes): " );
	strcat(finfo[2], fsize );

	finfo[3][0] = NULL;	// List terminator

cerr << "File::FileInfo : returning [0] = [" << finfo[0] << "]\n";
cerr << "File::FileInfo : returning [1] = [" << finfo[1] << "]\n";
cerr << "File::FileInfo : returning [2] = [" << finfo[2] << "]\n";
cerr << "File::FileInfo : returning [3] = [" << finfo[3] << "]\n";

	return (char**) finfo;
}
// End Member function FileInfo


// Summary -----------------------------------------------------------------
//
// Member Function PrintOn
//       Outputs the file to the specified output stream.
//
// End ---------------------------------------------------------------------
void      File::PrintOn ( ostream& s )
{
	TraceEntryExit t( "File", "PrintOn" );

	assert (s);   // Output stream should always be open

	class printfile : public ILineStrmFilter
	{
	public:
		printfile( ifstream& ii, ostream& oo )
		: ILineStrmFilter(ii,oo) { }
		void compute() { /* pass through */ };
	};
	// End class printfile

	if (this->Exists())
	{
		// Copy file contents to output stream

		ifstream f( this->FullName() );

		printfile pr(f,s);
		main_loop(&pr); /* Iterate */
	}
	/* else: File does not exist, so no output. */
}
// End Stream output Function operator << //



#ifdef TEST
//     ****

// **********************************
// main function for testing purposes
// **********************************

#define DEBUG

void main ( )
{
	TraceEntryExit t( "File test program", "main" );

	File f("file.C");   // This file !

	cout << "Start File test" << endl;
	cout << endl;

	cout << "File.h" << endl;
	cout << File("File.h");

	cout << f.FullName() << endl;
	cout << f;

	cout << "nofile.non" << endl;
	cout << File("nofile.non");

	cout << endl;
	cout << "End File test" << endl;
}
#endif /* TEST */


/* Original RCS change records from DOS version: */
/*****************************************************************************
 * $Log$
 * Revision 1.1  1996/05/07 14:29:37  njt
 * Initial revision
 *
 * Revision 2.4  92/01/16  00:01:06  ROOT_DOS
 * Attempting to get file reading working.  Still not successful.
 * 
 * Revision 2.3  92/01/14  22:11:16  ROOT_DOS
 * Entry and Exit tracing added to procedures using class TraceEntryExit.
 * 
 * Revision 2.2  91/07/10  00:00:00  njt
 * Converted function operator<< into function printOn.
 * Corrected use of PathName member functions and data.
 * Removed function getRecord, as it is now defined as an
 * in-line function in the header file.
 * 
 * Revision 2.1  91/03/22  00:00:00  njt
 * Minor changes to logic for deciding whether the file exists and if not
 * whether we should log a message.
 *
 * Revision 2.0  91/03/02            njt
 * Completely rewritten using the PathName class, and now providing a much
 * more general purpose interface to the file contents using record-level
 * access.
 *
 * Revision 1.1  91/02/09  17:46:19  njt
 * Initial version
 ****************************************************************************/

/******************************************************************************
 Change History
 ==============

Date          | Name  | Description
--------------+-------+-------------------------------------------------------
23-Apr-96	NJT	v1.1 - Initial UNIX version under SCCS control.
02-May-96	NJT	v1.2 - Removed all file iterator functionality from
			class File.
			Class FileIterator is not working properly yet.
******************************************************************************/
/* EOF */
