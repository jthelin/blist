/*  UTILDBUG.CPP  */

#include "utildbug.h"

#include <stdarg.h>
#include <stdio.h>
#include <iostream.h>
#include <strstream.h>

#define  MAX_LINE_SIZE  132

/*  Initialise static data members of class TraceEntryExit */
char *  TraceEntryExit::EntryPrefix	= ">>>> Entering ";
char *  TraceEntryExit::ExitPrefix	= "<<<< Exiting  ";
BOOL	TraceEntryExit::logEntryExits	= FALSE;

// Description -------------------------------------------------------------
//
// Constructor: TraceEntryExit
//
// End ---------------------------------------------------------------------
TraceEntryExit::TraceEntryExit (
                                const char * class_name,
                                const char * function_name )
: className( class_name ), functionName( function_name )
{
	if (logEntryExits)
                // Log entry message
		clog 	<< TraceEntryExit::EntryPrefix 
			<< className << "::" << functionName <<endl;
}
// End Constructor //


// Description -------------------------------------------------------------
//
// Destructor: ~TraceEntryExit
//	Destroys the object, and may or may not display the exit message
//	 depending on the value of the logEntryExits variable.
//
// End ---------------------------------------------------------------------
TraceEntryExit::~TraceEntryExit ( )
{
	if (logEntryExits)
		// Log entry message
		clog 	<< TraceEntryExit::ExitPrefix 
			<< className << "::" << functionName << endl;
}
// End Destructor //


/***************************************** commented out starts *************
static  ostream_withassign  debug_dest;

#define  MAX_BUFFER_SIZE  30000
static  char  near trace_buffer[MAX_BUFFER_SIZE];

void  set_debug_destination( ostream& ostr )
{
        // Flush any remaining output
        if (!debug_dest)  debug_dest.flush();

        // Set new output destination
        debug_dest = ostr;

}

void  dump_debug_buffer( void )
{
        clog << debug_dest;
}
 ***************************************** commented out ends *************/


/************************************************************************/
/* Function: do_debug                                                   */
/* Print an error message from the format-string FORMAT                 */
/*      with optional extra args as with printf.                        */
/************************************************************************/
void  do_debug( char * format, va_list args )
{
	static  char  line_buffer[MAX_LINE_SIZE];

/*
	if (debug_dest)
		// Debugging output destination not set up
		set_debug_destination(clog);
*/

	vsprintf(line_buffer,format,args);

	/*debug_dest*/
	clog << line_buffer << endl;
}


/******************************************************************************
 Change History
 ==============

Date          | Name  | Description
--------------+-------+-------------------------------------------------------
25-Apr-96	NJT	v1.1 - Initial UNIX version under SCCS control.
04-Sep-96	NJT	v1.2 - Moved TraceEntryExit ctor/dtor from inline to .C 
			file as it does not cope well with cfront inlining.
******************************************************************************/
/* EOF */
