// Contents ----------------------------------------------------------------
//
//	Contains the implementation for the File class
//
// End ---------------------------------------------------------------------

#include "File.h"

#include <cassert>
#include <chrono>
#include <ctime>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "filter.h"
#include "fileutil.h"
#include "TraceEntryExit.h"

class FilePrinter : public ILineStreamFilter {
public:
  FilePrinter(std::ifstream &ii, std::ostream &oo)
      : ILineStreamFilter(ii, oo) {}

  void compute() override { /* pass through */ };
};
// End class FilePrinter


// Summary -----------------------------------------------------------------
//
// Constructor for File object
//	No failure or warning messages will be logged if the file does not
//	exist if log_failures is false.
//
// End ---------------------------------------------------------------------
File::File(const std::string &filename, bool log_failures)
    : FilePath(filename) {
  TraceEntryExit t("File", "<constructor>", filename);

  if (!Exists()) {
    // File does not exist
    if (log_failures) {
      std::cerr << "**** ERROR:"
                << " File " << filename << " does not exist."
                << std::endl;
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
File::~File() {
  TraceEntryExit t("File", "<destructor>", this->FullName());
}
// End File Destructor //


// Summary -----------------------------------------------------------------
//
// Member Function ModificationDate
//	Return a string containing the modification date of a File.
//
// End ---------------------------------------------------------------------
std::string File::ModificationDate() const {
  return FileUtils::GetModificationDate(this->FullName());
}
// End Member function ModificationDate


// Summary -----------------------------------------------------------------
//
// Member Function FileSize
//	Return a File's size in bytes.
//
// End ---------------------------------------------------------------------
long File::FileSize() const
{
  return FileUtils::FileSize(this->FullName());
}
// End Member function Size


// Summary -----------------------------------------------------------------
//
// Member Function FileInfo
//	Return a (static) string array of file info details
//
// End ---------------------------------------------------------------------
std::vector<std::string> File::FileInfo() const
{
  auto file_info = std::vector<std::string>();

  auto out = std::stringstream();
  out << "File name: " << this->FullName();
  file_info.push_back(out.str());

  out = std::stringstream();
  out << "Last modified: " << this->ModificationDate();
  file_info.push_back(out.str());

  out = std::stringstream();
  out << "File size (bytes): " << this->FileSize();
  file_info.push_back(out.str());

  return file_info;
}
// End Member function FileInfo


// Summary -----------------------------------------------------------------
//
// Member Function PrintOn
//       Outputs the file to the specified output stream.
//
// End ---------------------------------------------------------------------
void File::PrintOn(std::ostream &s) {
  TraceEntryExit t("File", "PrintOn");

  assert (s);   // Output stream should always be open

  if (this->Exists()) {
    // Copy file contents to output stream
    std::ifstream file_reader(this->FullName());
    FilePrinter pr(file_reader, s);
    pr.main_loop(); /* Iterate */
  } else {
    std::cerr << "File " << this->FullName() << " does not exist, so no output." << std::endl;
  }
}
// End Stream output Function operator << //


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
23-Apr-96       NJT     v1.1 - Initial UNIX version under SCCS control.
02-May-96       NJT     v1.2 - Removed all file iterator functionality from class File.
                               Class FileIterator is not working properly yet.
******************************************************************************/
