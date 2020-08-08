#ifndef _FILTER_H
#define _FILTER_H

#ifndef __cplusplus
#error Requires C++ for use of these facilities
#endif

#include <cstring>
#include <iostream>

/*******************************************************************************
Class: IFilter

- Read an input stream, (possibly) perform some actions based on that input,
(possibly) produce an output stream, and (maybe) produce a final result.

Adapted from The C++ Programming Language (2nd Ed), Section 13.7, Page 455-6
*******************************************************************************/
class IFilter {
  int num_retries = 2;

public:
  // Exception
  class ERetry {
  public:
    virtual ~ERetry() = default;
    virtual const char* message() { return nullptr; }
  };

  virtual void start(){};

  virtual int retry() { return num_retries; }

  virtual int read() = 0; // Pure virtual function - sub-class must implement.

  virtual void write(){}; // Default = No output.

  virtual void compute(){};

  virtual int result() { return 0; };

  virtual ~IFilter() = default;

  int main_loop();
};
// End class IFilter

/*******************************************************************************
Class: ICharStreamFilter

- Version of IFilter for processing streams at the character level.

Adapted from The C++ Programming Language (2nd Ed), Section 13.7, Page 455-6
*******************************************************************************/
class ICharStreamFilter : public IFilter {
protected:
  std::istream& is;
  std::ostream& os;
  char          c = ' ';
  bool          bWriteOutput;

public:
  void compute() override = 0; // Pure virtual function - sub-class must implement.

  int read() override
  {
    is.get(c);
    return is.good();
  };

  void write() override
  {
    if (bWriteOutput) {
      os.put(c);
    }
  };

  ICharStreamFilter(std::istream& ii, std::ostream& oo) : is(ii), os(oo), bWriteOutput(true){};

  explicit ICharStreamFilter(std::istream& ii) : is(ii), os(std::clog), bWriteOutput(false){};
};
// End class ICharStreamFilter

/*******************************************************************************
Class: ILineStreamFilter

- Version of IFilter for processing streams at the line level.

Adapted from The C++ Programming Language (2nd Ed), Section 13.7, Page 455-6
*******************************************************************************/
class ILineStreamFilter : public IFilter {
protected:
  static constexpr char EOL           = '\n';
  static constexpr int  MAX_LINE_SIZE = 1024;
  std::istream&         is;
  std::ostream&         os;
  char                  buff[MAX_LINE_SIZE + 1];
  bool                  bWriteOutput;

public:
  void compute() override = 0; // Pure virtual function - sub-class must implement.

  int read() override
  {
    is.getline(buff, MAX_LINE_SIZE, EOL);
    return is.good();
  };

  void write() override
  {
    if (bWriteOutput) {
      os << buff << EOL;
    }
  };

  ILineStreamFilter(std::istream& ii, std::ostream& oo) : is(ii), os(oo)
  {
    bWriteOutput = true;
    memset(buff, '\0', MAX_LINE_SIZE + 1);
  };

  explicit ILineStreamFilter(std::istream& ii) : is(ii), os(std::clog)
  {
    bWriteOutput = false;
    memset(buff, '\0', MAX_LINE_SIZE + 1);
  };
};
// End class ILineStreamFilter

class LineCounter : public ILineStreamFilter {
  int num_lines;

public:
  void compute() override { num_lines++; };

  int result() override { return num_lines; };

  explicit LineCounter(std::istream& ii) : ILineStreamFilter(ii), num_lines(0) {}
};

class CharCounter : public ICharStreamFilter {
  int num_chars;

public:
  void compute() override { num_chars++; };

  int result() override { return num_chars; };

  explicit CharCounter(std::istream& ii) : ICharStreamFilter(ii), num_chars(0) {}
};

/*******************************************************************************
 Change History
 ==============

Date          | Name  | Description
--------------+-------+-------------------------------------------------------
30-Apr-96	NJT	v1.0 - Initial UNIX version.
01-May-96	NJT	v1.1 - Initial version placed under SCCS control.
				Added generic classes for Char and Line filters.
02-May-96	NJT	v1.2 - Add NL after each line output in ILineStreamFilter.
15-May-96	NJT	v1.3 - Added bWriteOutput flag to classes 
				ICharStreamFilter and ILineStreamFilter to cater
				for the common case where we want to iterate
				over an input file / stream and perform an 
				action on each line / char but not produce any 
				output until the end of processing.
*******************************************************************************/

#endif // _FILTER_H
