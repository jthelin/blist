//
// Implementation of Class TextBox
//

// Contents ----------------------------------------------------------------
//
//      TextBox::TextBox
//      TextBox::~TextBox
//     operator <<
//               main function for testing class implementation
//
// Description
//
//          Contains the implementation for the TextBox class
//
// End ---------------------------------------------------------------------


// Interface Declarations --------------------------------------------------
#include "TextBox.h"
// End Interface Declarations ----------------------------------------------

// Implementation Dependencies ----------------------------------------------
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <iomanip.h>
// End Implementation Dependencies -------------------------------------------


// Summary -----------------------------------------------------------------
//
// Constructor for TextBox object
//	Initialises the object data & stores the text message on the heap.
//
// End ---------------------------------------------------------------------
TextBox::TextBox(
	const char	text[],
	box_style	box_type,
	char		box_char )
{
	// Store the text message on the heap

	char * s = (char *) malloc( strlen(text)+1 );

	assert( s != NULL );

	if (s)  strcpy(s,text);

	// Initialise object data
	this->text = s;
	this->num_lines = 1;

	if (isprint(box_char))
		this->box_char = box_char;
	else
		// Specified box character is unprintable,
		// so override with a printable default.
		this->box_char = '*';

	this->box_type = box_type;
}
// End TextBox constructor //


// Summary -----------------------------------------------------------------
//
// Constructor for TextBox object
//	Initialises the object data & stores the multi-line text message on
//	 the heap.
//
// End ---------------------------------------------------------------------
TextBox::TextBox(
	const char *	text[],
	box_style	box_type,
	char		box_char )
{
	// Store the text message on the heap

	char * s, * p;
	int  num_lines = 0;
	int  area_size = 0;
	int  i;   // loop counter

	for ( i=0; *text[i] != '\0'; i++ )
		area_size += strlen(text[i]) + 1;  // count /0 string terminator

	num_lines = i;

	assert ( num_lines >= 0 );

	p = s = (char *) malloc( area_size + 1 );   // allow for final /0

	assert( s != NULL );

	// Copy lines onto heap
	for ( i=0; i<num_lines; i++)
	{
		strcpy( p, text[i] );
		p += strlen(text[i]) + 1;
	}
	*p = '\0';   // Add final terminator

	// Initialise object data
	this->text = s;
	this->num_lines = num_lines;

	if (isprint(box_char))
		this->box_char = box_char;
	else
		// Specified box character is unprintable,
		// so override with a printable default.
		this->box_char = '*';

	this->box_type = box_type;
}
// End TextBox constructor //


// Summary -----------------------------------------------------------------
//
// Destructor for TextBox object
//	Frees up the heap memory used to store the message string.
//
// End ---------------------------------------------------------------------
TextBox::~TextBox ( void )
{
	if (!this->text)  free(this->text);
}
// End TextBox Destructor //


// Summary -----------------------------------------------------------------
//
// Stream output Function operator <<
//	Outputs the specified TextBox object to the specified output stream.
//
// End ---------------------------------------------------------------------
ostream& operator << ( ostream& s, TextBox tb )
{
	unsigned int text_len = 0;
	char  *p;
	unsigned int  l;
	unsigned int	border_width,
			gap_width;
	unsigned int i,j;   // loop counts

	// Decide border and gap widths
	if (tb.box_type == TextBox::DOUBLE) 
		border_width = gap_width = 2;
	else if (tb.box_type == TextBox::BASIC)
	{
		border_width = 1;
		gap_width = 0;
	}
	else
		border_width = gap_width = 1;

	// Decide on the length of the longest line in the textbox.
	for ( l=0, p=tb.text; l<tb.num_lines; l++, p += strlen(p)+1 )
		if (text_len < strlen(p))
			text_len = strlen(p);

	// Top border
	for ( j=1; j<=border_width; j++ )
	{
		for ( i=1; i<=(text_len+2*border_width+2*gap_width); i++ )
			s << tb.box_char;
		s << endl;
	}
	// Top gap
	for ( j=1; j<=gap_width; j++ )
	{
		for ( i=1; i<=border_width; i++ )		s<< tb.box_char;
		for ( i=1; i<=text_len+2*gap_width; i++ )	s<< ' ';
		for ( i=1; i<=border_width; i++ )		s<< tb.box_char;
		s << endl;
	}

	// Output each line of the text message
	for ( l=0, p=tb.text; l<tb.num_lines; l++, p += strlen(p)+1 )
	{
		for ( i=1; i<=border_width; i++ )	s << tb.box_char;
		for ( i=1; i<=gap_width; i++ )		s << ' ';

		// Output this line of the text left justified in a field
		// big enough to take the longest line in the TextBox.
		s << setw(text_len) << setiosflags(ios::left) << p;

		for ( i=1; i<=gap_width; i++ )		s << ' ';
		for ( i=1; i<=border_width; i++ )	s << tb.box_char;
		s << endl;
	}

	// Bottom gap
	for ( j=1; j<=gap_width; j++ )
	{
		for ( i=1; i<=border_width; i++ )		s<< tb.box_char;
		for ( i=1; i<=text_len+2*gap_width; i++ )	s<< ' ';
		for ( i=1; i<=border_width; i++ )		s<< tb.box_char;
		s << endl;
	}
	// Bottom border
	for ( j=1; j<=border_width; j++ )
	{
		for ( i=1; i<=(text_len+2*border_width+2*gap_width); i++ )
			s << tb.box_char;
		s << endl;
	}

	return s;
}
// End Stream output Function operator << //



#ifdef TEST
//     ****

// **********************************
// main function for testing purposes
// **********************************

void main ( void )
{
	char *multi_line[] = { "Line1", "Line2", "Line3", "Last Line", "" };

	cout << "First Line" << endl;
	cout << endl;

	cout << TextBox ( "Text in a box" );

	cout << TextBox ( "More text in a box", TextBox::STANDARD );

	cout << TextBox ( "Even more text in a box", TextBox::DOUBLE, 'X' );

	cout << TextBox ( multi_line, TextBox::STANDARD );

	cout << endl;
	cout << "Last Line" << endl;
}
#endif


/* Original RCS change records from DOS version: */
/*****************************************************************************
 * $Log$
 * Revision 1.1  1996/05/07 14:29:38  njt
 * Initial revision
 *
 * Revision 1.1  91/02/09  17:46:43  njt
 * Initial revision
 *
 *****************************************************************************/

/******************************************************************************
 Change History
 ==============

Date          | Name  | Description
--------------+-------+-------------------------------------------------------
25-Apr-96	NJT	v1.1 - Initial UNIX version under SCCS control.
07-May-96	NJT	v1.2 - Moved box_style into class TextBox.
******************************************************************************/

/* EOF */
