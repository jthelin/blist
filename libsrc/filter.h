#ifndef _FILTER_H
#define _FILTER_H

// Use  CC -DNEXCEPTIONS ....   if the C++ compiler does not support Exceptions.

#ifndef __cplusplus
#error Requires C++ for use of these facilities
#endif

#include <iostream.h>
#include "Boolean.h"

/*******************************************************************************
Class: IFilter

- Read an input stream, (possibly) perform some actions based on that input,
(possibly) produce an output stream, and (maybe) produce a final result.

Adapted from The C++ Programming Language (2nd Ed), Section 13.7, Page 455-6
*******************************************************************************/
class IFilter {
public:
	// Exception
	class ERetry {
	public:
		virtual const char * message()  { return 0; }
	};

	virtual void start() { };
	virtual int retry() { return 2; }
	virtual int read() = 0;
	virtual void write() { };
	virtual void compute() { };
	virtual int result() = 0;
};
// End class IFilter


// Function main_loop (using Exceptions unless NEXCEPTIONS is defined)
int main_loop( IFilter* p )
{
	for(;;)	// Loop forever
	{

#ifndef NEXCEPTIONS

		try {

#endif /* NEXCEPTIONS */

			p->start();
			while (p->read())
			{
				p->compute();
				p->write();
			}
			return p->result();	// Exit loop

#ifndef NEXCEPTIONS

		}
		catch (IFilter::ERetry& m)
		{
			cout << m.message() << '\n';
			int i = p->retry();
			if (i) return i;	// Exit loop
		}
		catch (...)
		{
			cout << "Fatal filter error\n";
			return 1;	// Exit loop
		}

#endif /* NEXCEPTIONS */

	}
	// Never reached
};


/*******************************************************************************
Class: ICharStrmFilter

- Version of IFilter for processing streams at the character level.

Adapted from The C++ Programming Language (2nd Ed), Section 13.7, Page 455-6
*******************************************************************************/
class ICharStrmFilter : public IFilter
{
protected:
	istream& is;
	ostream& os;
	char c;
	BOOL bWriteOutput;
public:
	virtual int read() { is.get(c); return is.good(); };
	virtual void compute() = 0;	// Pure virtual function
	virtual void write() { if (bWriteOutput) os.put(c); };
	virtual int result() { return 0; };

	ICharStrmFilter( istream& ii, ostream& oo )
	: is(ii), os(oo), bWriteOutput(TRUE) { };
	ICharStrmFilter( istream& ii )
	: is(ii), os(NULL), bWriteOutput(FALSE) { };
};
// End class ICharStrmFilter


/*******************************************************************************
Class: ILineStrmFilter

- Version of IFilter for processing streams at the line level.

Adapted from The C++ Programming Language (2nd Ed), Section 13.7, Page 455-6
*******************************************************************************/
class ILineStrmFilter : public IFilter
{
protected:
	istream& is;
	ostream& os;
	enum { MAX_LINE_SIZE = 1024 };
	char buff[MAX_LINE_SIZE+1];
	BOOL bWriteOutput;
public:
	virtual int read()
	{
		is.getline( buff, MAX_LINE_SIZE, '\n' );
		buff[MAX_LINE_SIZE] = 0;	// Add NULL terminator
		return is.good();
	};
	virtual void compute() = 0;	// Pure virtual function
	virtual void write() { if (bWriteOutput) os << buff << '\n'; };
	virtual int result() { return 0; };

	ILineStrmFilter( istream& ii, ostream& oo )
	: is(ii), os(oo), bWriteOutput(TRUE) { };
	ILineStrmFilter( istream& ii )
	: is(ii), os(NULL), bWriteOutput(FALSE) { };
};
// End class ILineStrmFilter


/*******************************************************************************
 Change History
 ==============

Date          | Name  | Description
--------------+-------+-------------------------------------------------------
30-Apr-96	NJT	v1.0 - Initial UNIX version.
01-May-96	NJT	v1.1 - Initial version placed under SCCS control.
				Added generic classes for Char and Line filters.
02-May-96	NJT	v1.2 - Add NL after each line output in ILineStrmFilter.
15-May-96	NJT	v1.3 - Added bWriteOutput flag to classes 
				ICharStrmFilter and ILineStrmFilter to cater
				for the common case where we want to iterate
				over an input file / stream and perform an 
				action on each line / char but not produce any 
				output until the end of processing.
*******************************************************************************/

#endif /* ifndef _FILTER_H */
/* EOF */
