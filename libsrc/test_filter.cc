
#include "filter.h"

#include <iostream.h>


class mycharfilter : public ICharStrmFilter
{
	int nchar;
public:
	void compute() { nchar++; };
	void write() { };	// No output
	int result()
	{
		cout << nchar << " characters read\n";
		return 0;
	};

	mycharfilter( istream& ii )
	: ICharStrmFilter(ii), nchar(0) { }
};
// End class mycharfilter

class mylinefilter : public ILineStrmFilter
{
	int nlines;
public:
	void compute() { nlines++; };
	void write() { };	// No output
	int result()
	{
		cout << nlines << " lines read\n";
		return 0;
	};

	mylinefilter( istream& ii )
	: ILineStrmFilter(ii), nlines(0) { }
};
// End class mylinefilter


int main()
{

//	cerr << "test_filter: Read from cin stream and count characters.\n";
//	mycharfilter f(cin);

	cerr << "test_filter: Read from cin stream and count lines.\n";
	mylinefilter f(cin);

	return main_loop(&f);
};
// End function main

