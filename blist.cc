//
//  BLIST
//
// Output a text file to stdout (for redirection) preceded
//       by a header identifying the file.
//
/* Program information */
extern "C" {
#include <proginfo.h>
}
char *  ProgName        = "blist";
char *  ProgDesc        = "Bulk list text file contents and file info to stdout.";
char *  ProgAuthor      = "J.Thelin";
char *  ProgVer         = "2.02";
char *  ProgRelStat     = "GA";
char *  ProgDate        = "23-May-96";

static char * ident_blist = "%Z%  $RCSfile$($Revision$)  $Date$__ - njt";

#include <stdlib.h>
#include <string.h>
#include <iostream.h>
#include <time.h>

#include "utildbug.h"
#include "File.h"
#include "TextBox.h"

// Default values
// --------------
BOOL		_debug		= 0;
const int	DEF_TAB_SIZE	= 4;
BOOL		bFormFeed	= FALSE;

// Call as (for example)  cout << NL;
// Function: NL - Output a new line onto a stream.
inline  ostream&  NL ( ostream& s )   { return ( s.put('\n') ); }
// Function: FF - Output a form feed (new page) onto a stream.
inline  ostream&  FF ( ostream& s )   { return ( s.put('\f') ); }


void ShowUsage()
{
// Show program usage message

cerr    << "Usage: " << ProgName
	<< " [-t tabsize]"
	<< " [-F]"
	<< " [-D]"
	<< " files ......"
	<< endl;
cerr	<< endl
	<< "  -t tabsize      = Set TAB expansion size." <<endl
	<< "                    (Not yet implemented)" <<endl
	<< "  -F              = Set Form Feed mode on." <<endl
	<< "  -D              = Set debug mode on." <<endl
	<< "                    (Development use only)." <<endl
	<< endl;
}

void main ( int argc, char *argv[] )
{
	int i;
	int     errflag = 0;
	int     c;

	// Data for getopts
	extern char *   optarg;
	extern int      optind;

	// Parameter values
	int  tab_size;

	// Sign-on message
	SIGNON;
	cerr    << ProgName << " - " << ProgDesc << endl << endl;

	// Check arguments
	if( argc < 2 )
		errflag++;

	// Set default values for options
	tab_size  = DEF_TAB_SIZE;

	// Check option values
        while ((c = getopt( argc, argv, "t:FD" )) != EOF)
        {
                switch (c)
                {
                case 't':
                        /* Tab size */
                        tab_size = atoi(optarg);
			cerr	<< ProgName << ":"
				<< " Tab size set to " << tab_size << endl;
                        break;
                case 'D':
                        /* Debug mode */
                        _debug = 1;
			TraceEntryExit::SetLogging(TRUE);
			cerr	<< ProgName << ":"
				<< " Debug mode set to on." << endl;
                        break;
                case 'F':
                        /* FormFeed mode */
                        bFormFeed = 1;
			cerr	<< ProgName << ":"
				<< " FordFeed mode set to on." << endl;
                        break;
                case '?':
                        /* Invalid option specified */
                        errflag++;
                }
        }

        if ( errflag > 0 )
        {
		// Show usage summary
		ShowUsage();
                exit(1);
        }

	// Process files
	for (i=optind; i<argc; i++)
	{
		char * fname = argv[i];
		File f(fname);

		if ( f.Exists() )
		{
			// List this file
			// ==============

			// Get file info details
/*	
			char** fi;
			fi = f.FileInfo();
cerr << "FInfo[0]=[" << fi[0] << "]\n";
cerr << "FInfo[1]=[" << fi[1] << "]\n";
cerr << "FInfo[2]=[" << fi[2] << "]\n";
cerr << "FInfo[3]=[" << fi[3] << "]\n";
*/
			const char * fi = f.FullName();

			// Output file header
			cout << TextBox(fi,TextBox::DOUBLE);

			cout << NL;  // Blank line

			// Output file contents
			f.PrintOn(cout);

			if (bFormFeed)
				cout << FF;	// Start new page
			else
				cout << endl;	// Just insert a blank line

			cout.flush();
		}
		else
		{
			cerr	<< "**** ERROR :  "
				<< " File " << fname
				<< " does not exist" << endl;
			exit (1);
		}
	}
	exit (0);
}


/* Original RCS change records from DOS version: */
/******************************************************************************
 * $Log$
 * Revision 1.3  1996/05/23 15:24:02  njt
 * Added FormFeed mode to not output FF by default.
 *
 * Revision 1.1  91/02/09  17:43:39  njt
 * Initial revision
*****************************************************************************/

/******************************************************************************
 Change History
 ==============

Date          | Name  | Description
--------------+-------+-------------------------------------------------------
02-May-96	NJT	v2.00 - Initial UNIX version under SCCS control.
22-May-96	NJT	v2.01 - Moved infrastructure and utility classes to lib.
23-May-96	NJT	v2.02 - Added FormFeed mode to not output FF by default.
******************************************************************************/
/* EOF */
