#include "File.h"

#include <cassert>
#include <fstream>
#include <sstream>
#include <utility>

#include "TraceEntryExit.h"
#include "fileutil.h"
#include "filter.h"

class FilePrinter : public ILineStreamFilter {
public:
  FilePrinter(std::istream& ii, std::ostream& oo) :
      ILineStreamFilter(ii, oo)
  {
  }

  void compute() override{/* pass through */};
};

File::File(const std::string& file_path, bool log_failures) : _file(std::filesystem::path(file_path))
{
  TraceEntryExit t("File", "<constructor>", _file.generic_string());

  if (!std::filesystem::exists(_file)) {
    // File does not exist
    if (log_failures) {
      std::cerr << "**** ERROR:"
                << " File " << file_path << " does not exist." << std::endl;
    }
  }
}

File::~File()
{
  TraceEntryExit t("File", "<destructor>", _file.generic_string());
}

std::string File::ModificationDate() const
{
  return FileUtils::GetModificationDate(_file);
}

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

void File::PrintTo(std::ostream& s)
{
  TraceEntryExit t("File", "PrintTo", _file.generic_string());

  assert(s); // Output stream should always be open

  if (this->Exists()) {
    // Copy file contents to output stream
    auto file_reader  = std::ifstream(_file);
    auto file_printer = FilePrinter(file_reader, s);
    file_printer.main_loop(); /* Iterate */
  }
  else {
    std::cerr << "File " << this->FullName() << " does not exist, so no output." << std::endl;
  }
}

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
