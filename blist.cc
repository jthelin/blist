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
const std::string ProgVer = "2.03";
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

// Call as (for example)  std::cout << NL;
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

/**
 * List this file to the specified output stream.
 * @param f - The file to be processed.
 * @param out - The output stream to use.
 * @param flush - Whether the output stream should be flushed after processing.
 */
void ProcessFile(
    File &f,
    std::ostream &out = std::cout,
    bool useFormFeed = false,
    bool flush = true) {
  // List this file
  // ==============

  // Get file info details
/*
  char** file_info;
  file_info = f.FileInfo();
  std::cerr << "FInfo[0]=[" << file_info[0] << "]\n";
  std::cerr << "FInfo[1]=[" << file_info[1] << "]\n";
  std::cerr << "FInfo[2]=[" << file_info[2] << "]\n";
  std::cerr << "FInfo[3]=[" << file_info[3] << "]\n";
*/
  const std::string file_info = f.FullName();

  // Output file header
  out << TextBox(file_info, TextBox::DOUBLE);

  out << NL;  // Blank line

  // Output file contents
  f.PrintOn(out);

  if (useFormFeed) {
    out << FF;  // Start new page
  } else {
    out << std::endl;  // Just insert a blank line
  }

  if (flush) {
    out.flush();
  }
}

int blist_main(int argc, char **argv) {
  // Parameter values
  int tab_size = DEF_TAB_SIZE;
  bool useFormFeed = false;

  // Sign-on message
  ProgramSignOn() << ProgName << " - " << ProgDesc << std::endl << std::endl;

  // Check arguments
  int arg_error_count = 0;
  if (argc < 2) {
    arg_error_count++;
  }

  // Check option values
  int c;
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
        _debug = true;
        TraceEntryExit::SetLogging(true);
        std::cerr << ProgName << ":"
                  << " Debug mode set to on." << std::endl;
        break;
      case 'F':
        /* FormFeed mode */
        useFormFeed = true;
        std::cerr << ProgName << ":"
                  << " FormFeed mode set to on." << std::endl;
        break;
      case '?':
      default:
        /* Invalid option specified */
        arg_error_count++;
    }
  }

  if (arg_error_count > 0) {
    // Show usage summary
    ShowUsage();
    exit(1);
  }

  // Process files
  for (auto i = optind; i < argc; i++) {
    char *file_name = argv[i];
    File f(file_name);

    if (f.Exists()) {
      // List this file
      ProcessFile(f, std::cout, useFormFeed);
    } else {
      std::cerr << "**** ERROR :  "
                << " File " << file_name
                << " does not exist" << std::endl;
      exit(1);
    }
  } // End process each file
  exit(0);
}


/******************************************************************************
 Change History
================

Date          | Name  | Description
--------------+-------+-------------------------------------------------------
09-Feb-1991    NJT     v1.1 - Initial version.
02-May-1996    NJT     v2.00 - Initial UNIX version under SCCS control.
22-May-1996    NJT     v2.01 - Moved infrastructure and utility classes to lib.
23-May-1996    NJT     v2.02 - Added FormFeed mode to not output FF by default.
02-Aug-2019    NJT     v2.03 - Updated code to use "Modern C++".
******************************************************************************/
