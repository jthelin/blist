//
//  BLIST
//
// Output a text file to stdout (for redirection) preceded
//       by a header identifying the file.
//

#include <string>

#include "blist.h"

/* Program information */
#include "libsrc/proginfo.h"

const std::string ProgName = "blist";
const std::string ProgDesc = "Bulk list text file contents and file info to stdout.";
const std::string ProgAuthor = "J.Thelin";
const std::string ProgVer = "2.02";
const std::string ProgReleaseStatus = "GA";
const std::string ProgDate = "02-Aug-2019";

static std::string ident_blist = "%Z%  $RCSfile$($Revision$)  $Date$__ - njt";

#include <cstdlib>
#include <iostream>
#include <getopt.h>

#include "libsrc/utildbug.h"
#include "libsrc/File.h"
#include "libsrc/TextBox.h"

// Default values
// --------------
bool _debug = false;
const int DEF_TAB_SIZE = 4;
bool bFormFeed = false;

// Call as (for example)  cout << NL;
// Function: NL - Output a new line onto a stream.
inline std::ostream &NL(std::ostream &s) { return (s.put('\n')); }

// Function: FF - Output a form feed (new page) onto a stream.
inline std::ostream &FF(std::ostream &s) { return (s.put('\f')); }


void ShowUsage() {
// Show program usage message

  std::cerr
      << "Usage: " << ProgName
      << " [-t tabsize]"
      << " [-F]"
      << " [-D]"
      << " files ......"
      << std::endl;
  std::cerr
      << std::endl
      << "  -t tabsize      = Set TAB expansion size." << std::endl
      << "                    (Not yet implemented)" << std::endl
      << "  -F              = Set Form Feed mode on." << std::endl
      << "  -D              = Set debug mode on." << std::endl
      << "                    (Development use only)." << std::endl
      << std::endl;
}

int blist_main(int argc, char **argv) {
  int i;
  int errflag = 0;
  int c;

  // Parameter values
  int tab_size;

  // Sign-on message
  ProgramSignOn() << ProgName << " - " << ProgDesc << std::endl << std::endl;

  // Check arguments
  if (argc < 2) {
    errflag++;
  }

  // Set default values for options
  tab_size = DEF_TAB_SIZE;

  // Check option values
  while ((c = getopt(argc, argv, "t:FD")) != EOF) {
    switch (c) {
      case 't':
        /* Tab size */
        tab_size = atoi(optarg);
        std::cerr << ProgName << ":"
                  << " Tab size set to " << tab_size << std::endl;
        break;
      case 'D':
        /* Debug mode */
        _debug = 1;
        TraceEntryExit::SetLogging(true);
        std::cerr << ProgName << ":"
                  << " Debug mode set to on." << std::endl;
        break;
      case 'F':
        /* FormFeed mode */
        bFormFeed = 1;
        std::cerr << ProgName << ":"
                  << " FordFeed mode set to on." << std::endl;
        break;
      case '?':
      default:
        /* Invalid option specified */
        errflag++;
    }
  }

  if (errflag > 0) {
    // Show usage summary
    ShowUsage();
    exit(1);
  }

  // Process files
  for (i = optind; i < argc; i++) {
    char *fname = argv[i];
    File f(fname);

    if (f.Exists()) {
      // List this file
      // ==============

      // Get file info details
/*
			char** fi;
			fi = f.FileInfo();
std::cerr << "FInfo[0]=[" << fi[0] << "]\n";
std::cerr << "FInfo[1]=[" << fi[1] << "]\n";
std::cerr << "FInfo[2]=[" << fi[2] << "]\n";
std::cerr << "FInfo[3]=[" << fi[3] << "]\n";
*/
      const std::string fi = f.FullName();

      // Output file header
      std::cout << TextBox(fi, TextBox::DOUBLE);

      std::cout << NL;  // Blank line

      // Output file contents
      f.PrintOn(std::cout);

      if (bFormFeed)
        std::cout << FF;  // Start new page
      else
        std::cout << std::endl;  // Just insert a blank line

      std::cout.flush();
    } else {
      std::cerr << "**** ERROR :  "
                << " File " << fname
                << " does not exist" << std::endl;
      exit(1);
    }
  }
  exit(0);
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
02-May-96       NJT     v2.00 - Initial UNIX version under SCCS control.
22-May-96       NJT     v2.01 - Moved infrastructure and utility classes to lib.
23-May-96       NJT     v2.02 - Added FormFeed mode to not output FF by default.
******************************************************************************/
