#ifndef _FILTER_H
#define _FILTER_H

// Use  CC -DNEXCEPTIONS ....   if the C++ compiler does not support Exceptions.

#ifndef __cplusplus
#error Requires C++ for use of these facilities
#endif

#include <iostream>
#include <cstring>

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
    virtual const char *message() { return nullptr; }
  };

  virtual void start() {};

  virtual int retry() { return num_retries; }

  virtual int read() = 0; // Pure virtual function - sub-class must implement.

  virtual void write() {}; // Default = No output.

  virtual void compute() {};

  virtual int result() { return 0; };

  virtual ~IFilter() = default;
};
// End class IFilter


// Function main_loop (using Exceptions unless NEXCEPTIONS is defined)
int main_loop(IFilter *p) {
  for (;;)  // Loop forever
  {

#ifndef NEXCEPTIONS
    try {
#endif /* NEXCEPTIONS */

      p->start();
      while (p->read()) {
        p->compute();
        p->write();
      }
      return p->result();  // Exit loop

#ifndef NEXCEPTIONS
    }
    catch (IFilter::ERetry &m) {
      std::cerr << m.message() << std::endl;
      int i = p->retry();
      if (i) {
        return -i;  // Exit loop
      }
    }
    catch (...) {
      std::cerr << "Fatal filter error" << std::endl;
      return -10;  // Exit loop
    }
#endif /* NEXCEPTIONS */

  } // End forever loop
  // Not reached.
}


/*******************************************************************************
Class: ICharStreamFilter

- Version of IFilter for processing streams at the character level.

Adapted from The C++ Programming Language (2nd Ed), Section 13.7, Page 455-6
*******************************************************************************/
class ICharStreamFilter : public IFilter {
protected:
  std::istream &is;
  std::ostream &os;
  char c = ' ';
  bool bWriteOutput;

public:
  void compute() override = 0;  // Pure virtual function - sub-class must implement.

  int read() override {
    is.get(c);
    return is.good();
  };

  void write() override {
    if (bWriteOutput) {
      os.put(c);
    }
  };

  ICharStreamFilter(std::istream &ii, std::ostream &oo)
      : is(ii), os(oo), bWriteOutput(true) {};

  explicit ICharStreamFilter(std::istream &ii)
      : is(ii), os(std::clog), bWriteOutput(false) {};
};
// End class ICharStreamFilter


/*******************************************************************************
Class: ILineStreamFilter

- Version of IFilter for processing streams at the line level.

Adapted from The C++ Programming Language (2nd Ed), Section 13.7, Page 455-6
*******************************************************************************/
class ILineStreamFilter : public IFilter {
protected:
  static constexpr char EOL = '\n';
  static constexpr int MAX_LINE_SIZE = 1024;
  std::istream &is;
  std::ostream &os;
  char buff[MAX_LINE_SIZE + 1];
  bool bWriteOutput;

public:
  void compute() override = 0;  // Pure virtual function - sub-class must implement.

  int read() override {
    is.getline(buff, MAX_LINE_SIZE, EOL);
    return is.good();
  };

  void write() override {
    if (bWriteOutput) {
      os << buff << EOL;
    }
  };

  ILineStreamFilter(std::istream &ii, std::ostream &oo)
      : is(ii), os(oo) {
    bWriteOutput = true;
    memset(buff, '\0', MAX_LINE_SIZE + 1);
  };

  explicit ILineStreamFilter(std::istream &ii)
      : is(ii), os(std::clog) {
    bWriteOutput = false;
    memset(buff, '\0', MAX_LINE_SIZE + 1);
  };
};
// End class ILineStreamFilter


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

#endif /* ifndef _FILTER_H */
