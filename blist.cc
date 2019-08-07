//  BLIST
//
// Output a text file to stdout (for redirection) preceded by a header identifying the file.

#include <string>
#include <cstdlib>
#include <iostream>
#include <getopt.h>

#include "libsrc/proginfo.h"
#include "libsrc/utildbug.h"
#include "libsrc/File.h"
#include "libsrc/TextBox.h"

#include "blist.h"

/* Program information */
std::string ProgInfo::Name          = "blist";
std::string ProgInfo::Desc          = "Bulk list text file contents and file info to stdout.";
std::string ProgInfo::Author        = "J.Thelin";
std::string ProgInfo::Version       = "2.04";
std::string ProgInfo::ReleaseStatus = "GA";
std::string ProgInfo::ReleaseDate   = "08-Aug-2019";

/**
 * Show program usage message
 */
void ShowUsage() {
  std::cerr
      << "Usage: " << ProgInfo::Name
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
 * Parse command line arguments.
 * @param argc - Argument count.
 * @param argv - Argument strings.
 * @param params - Parameter values to be populated with command line overrides.
 * @return TRUE if there were no errors found when parsing command line arguments.
 */
bool ParseArguments(int argc, char *const *argv, blist_params &params) {
  const std::string& ProgName = ProgInfo::Name;

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
        params.tab_size = atoi(optarg);
        std::cerr << ProgName << ":"
                  << " Tab size set to " << params.tab_size << std::endl;
        break;
      case 'D':
        /* Debug mode */
        params._debug = true;
        TraceEntryExit::SetLogging(true);
        std::cerr << ProgName << ":"
                  << " Debug mode set to on." << std::endl;
        break;
      case 'F':
        /* FormFeed mode */
        params.useFormFeed = true;
        std::cerr << ProgName << ":"
                  << " FormFeed mode set to on." << std::endl;
        break;
      case '?':
      default:
        /* Invalid option specified */
        arg_error_count++;
    }
  }

  // Gather file names
  for (auto i = optind; i < argc; i++) {
    char *file_name = argv[i];
    if (params._debug) { std::cerr << "File argument '" << file_name << "'\n"; }
    params.files.emplace_back(std::string(file_name));
  }

  return (arg_error_count == 0);
}

/**
 * List this file to the specified output stream.
 * @param f - The file to be processed.
 * @param params - Parameters to use when processing this file.
 * @param out - The output stream to use.
 */
void ProcessFile(
    File &f,
    const blist_params &params,
    std::ostream &out = std::cout) {
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
  const std::vector<std::string> file_info = {f.FullName()};

  // Output file header
  out << TextBox(file_info, TextBox::DOUBLE);

  out << NL;  // Blank line

  // Output file contents
  f.PrintOn(out);

  if (params.useFormFeed) {
    out << FF;  // Start new page
  } else {
    out << std::endl;  // Just insert a blank line
  }

  if (params.flush) {
    out.flush();
  }
}

int blist_main(int argc, char **argv) {
  // Sign-on message
  ProgramSignOn() << ProgInfo::Name << " - " << ProgInfo::Desc << std::endl << std::endl;

  // Parameter values
  blist_params params{};
  bool args_ok = ParseArguments(argc, argv, params);
  if (!args_ok) {
    // Show usage summary
    ShowUsage();
    exit(1);
  }

  // Process files
  for (const auto &file_name : params.files) {
    if (params._debug) { std::cerr << "Processing file '" << file_name << "'\n"; }

    File f(file_name);

    if (f.Exists()) {
      // List this file
      ProcessFile(f, params, std::cout);
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
