#ifndef _TEXTBOX_H
#define _TEXTBOX_H

//
// Class TextBox
//
// Contents ----------------------------------------------------------------
//
//	Contains the class declaration for the TextBox class
//
// End ---------------------------------------------------------------------


// Interface Dependencies ---------------------------------------------------
#include <iostream.h>
// End Interface Dependencies ------------------------------------------------


// Description -------------------------------------------------------------
//
// Class: TextBox
//	A message to be output surrounded by a box of text characters,
//	 using a specified box character, and using a variety of box styles.
//
// Constructor:
//	TextBox
//		Stores the message to be output later in the heap.
//
// Destructor:
//	~TextBox
//
// Stream output functions:
//	operator <<
//		Puts the TextBox out to the specified output stream.
//
// Inherited Members
//	None.
//
// End ---------------------------------------------------------------------
class TextBox
{
public:
	enum box_style { BASIC, STANDARD, DOUBLE };
protected:
	char *		text;
	int		num_lines;
	char		box_char;
	box_style	box_type;
public:
			TextBox(
				const char text[],
				box_style box_type = TextBox::STANDARD,
				char box_char = '*' );
			TextBox(
				const char * text[],
				box_style box_type = TextBox::STANDARD,
				char box_char = '*' );
			~TextBox ( void );

	friend  ostream& operator << ( ostream& s, TextBox tb );
};


/* Original RCS change records from DOS version: */
/*****************************************************************************
 * $Log$
 * Revision 1.1  1996/05/07 14:29:35  njt
 * Initial revision
 *
 * Revision 1.1  91/02/09  17:50:06  njt
 * Initial revision
 ****************************************************************************/

/******************************************************************************
 Change History
 ==============

Date          | Name  | Description
--------------+-------+-------------------------------------------------------
25-Apr-96	NJT	v1.1 - Initial UNIX version under SCCS control.
07-May-96	NJT	v1.2 - Moved box_style enum into class TextBox.
******************************************************************************/

#endif // ifndef _TEXTBOX_H //
/* EOF */
