#pragma once

#ifndef __cplusplus
#error Requires C++ for use of these facilities
#endif

#include <array>
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

  virtual void start() {}

  virtual int retry() { return num_retries; }

  virtual int read() = 0; // Pure virtual function - sub-class must implement.

  virtual void write() {} // Default = No output.

  virtual void compute() {}

  virtual int result() { return 0; }

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
  std::ostream& os = std::clog;
  char          c  = ' ';
  bool          bWriteOutput;

public:
  void compute() override = 0; // Pure virtual function - sub-class must implement.

  int read() override
  {
    is.get(c);
    return is.good();
  }

  void write() override
  {
    if (bWriteOutput) {
      os.put(c);
    }
  }

  [[maybe_unused]] ICharStreamFilter(std::istream& ii, std::ostream& oo) : is(ii), os(oo), bWriteOutput(true) {}

  explicit ICharStreamFilter(std::istream& ii) : is(ii), bWriteOutput(false) {}
};
// End class ICharStreamFilter

/*******************************************************************************
Class: ILineStreamFilter

- Version of IFilter for processing streams at the line level.

Adapted from The C++ Programming Language (2nd Ed), Section 13.7, Page 455-6
*******************************************************************************/
class ILineStreamFilter : public IFilter {
protected:
  static constexpr char               EOL           = '\n';
  static constexpr int                MAX_LINE_SIZE = 1024;
  std::istream&                       is;
  std::ostream&                       os = std::clog;
  std::array<char, MAX_LINE_SIZE + 1> buff{};
  bool                                bWriteOutput;

public:
  void compute() override = 0; // Pure virtual function - sub-class must implement.

  int read() override
  {
    is.getline(buff.data(), MAX_LINE_SIZE, EOL);
    return is.good();
  }

  void write() override
  {
    if (bWriteOutput) {
      os << buff.data() << EOL;
    }
  }

  ILineStreamFilter(std::istream& ii, std::ostream& oo) : is(ii), os(oo), bWriteOutput(true)
  {
    std::memset(buff.data(), '\0', buff.size());
  }

  explicit ILineStreamFilter(std::istream& ii) : is(ii), bWriteOutput(false)
  {
    std::memset(buff.data(), '\0', buff.size());
  }
};
// End class ILineStreamFilter

class LineCounter : public ILineStreamFilter {
  int num_lines = 0;

public:
  void compute() override { num_lines++; }

  int result() override { return num_lines; }

  explicit LineCounter(std::istream& ii) : ILineStreamFilter(ii) {}
};

class CharCounter : public ICharStreamFilter {
  int num_chars = 0;

public:
  void compute() override { num_chars++; }

  int result() override { return num_chars; }

  explicit CharCounter(std::istream& ii) : ICharStreamFilter(ii) {}
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
