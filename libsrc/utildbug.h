#ifndef _UTILDBUG_H
#define _UTILDBUG_H

// Contents ----------------------------------------------------------------
//
//          Defines the TraceEntryExit class that provides general purpose
//              tracing facilities.
//
// End ---------------------------------------------------------------------

#ifndef __cplusplus
#error Requires C++ for use of these facilities
#endif

#include <string>
#include <cstdarg>
#include <iostream>

extern bool _debug;   // Debugging flag - usually define in main

/*****************************************************************************/
/* General debugging messages                                                */
/*****************************************************************************/

extern void do_debug(std::string &format, va_list args);

//void inline debug(std::string &fmt, ...) {
//  va_list args;
//
//  if (_debug) {
//    // Debugging flag is on
//    va_start(args, &fmt);
//    do_debug(fmt, args);
//    va_end(args);
//  }
//}

/*****************************************************************************/
/* Checking of PRE and POST conditions                                       */
/*****************************************************************************/

/******************************************************************************
** Need the following declaration in the main program module:

#ifdef DEBUG
#include <fstream.h>
ofstream errlog("err.dat");
#endif

******************************************************************************/

#ifdef DEBUG

#include <fstream.h>
extern ofstream errlog;

/* PRECONDITIONS : REQUIRE(b) */
/* -------------------------- */
#define	REQUIRE(b) \
  if (!(b)) \
    errlog	<< "PRECONDITION (REQUIRE) failed at " \
      << __FILE__ << " line " << __LINE__ << endl \
      << "Check was [ #b ]" << endl

/* POSTCONDITIONS : ENSURE(b) */
/* -------------------------- */
#define	ENSURE(b) \
  if (!(b)) \
    errlog	<< "POSTCONDITION (ENSURE) failed at " \
      << __FILE__ << " line " << __LINE__ << endl \
      << "Check was [ #b ]" << endl

#else
/* No debugging */
#define REQUIRE(b)
#define ENSURE(b)
#endif

/*****************************************************************************/

/******************************************************************************
#define PLACE(v,f) "File:%s Line:%d " #v f, __FILE__, __LINE__, v


#define  trace_int(i)           debug( PLACE( i,  "=%d"  ) )
#define  trace_hex_int(hi)      debug( PLACE( hi, "=%x"  ) )
#define  trace_long(l)          debug( PLACE( l,  "=%l"  ) )
#define  trace_hex_long(hl)     debug( PLACE( hl, "=%lx" ) )
#define  trace_string(s)        debug( PLACE( s,  "=%s"  ) )
#define  trace_float(f)         debug( PLACE( f,  "=%g"  ) )
#define  trace_double(d)        debug( PLACE( d,  "=%lg" ) )
#define  trace_long_double(ld)  debug( PLACE( ld, "=%Lg" ) )

#define  trace_char(c)          debug( PLACE( c,  "=%c"  ) )
******************************************************************************/

/*****************************************************************************/
/* Function Entry and Exit tracing                                           */
/*****************************************************************************/

// Description -------------------------------------------------------------
//
// Class: TraceEntryExit
//	Provides entry and exit tracing facilities.
//	When the destructor is called for an object of this class, an
//	 appropriate message will be logged to the stream clog if
//	 logEntryExits is TRUE.
//
// End ---------------------------------------------------------------------
class TraceEntryExit {
private:
  static std::string EntryPrefix;
  static std::string ExitPrefix;

  static bool logEntryExits; // If true, then entry and exit trace will be logged.

  const std::string &className;
  const std::string &functionName;
public:
  TraceEntryExit(
      const std::string &className,
      const std::string &functionName);

  ~TraceEntryExit();

  static void SetLogging(bool bLogTrace) {
    TraceEntryExit::logEntryExits = bLogTrace;
  };
};
// End Class TraceEntryExit


/* Original RCS change records from DOS version: */
/******************************************************************************
 * $Log$
 * Revision 2.2  1996/09/04 14:09:15  njt
 * Moved TraceEntryExit ctor/dtor from inline to .C file as did not work.
 *
 * Revision 1.1  92/01/14  22:13:07  ROOT_DOS
 * Added class TraceEntryExit.
*****************************************************************************/

/******************************************************************************
 Change History
 ==============

Date          | Name  | Description
--------------+-------+-------------------------------------------------------
25-Apr-96       NJT     v1.1 - Initial UNIX version under SCCS control.
30-Jul-96       NJT     v2.1 - Added functions for checking PRE and POST condns.
04-Sep-96       NJT     v2.2 - Moved TraceEntryExit ctor/dtor from inline to .C
                               file as it does not cope well with cfront inlining.
******************************************************************************/

#endif /* _UTILDBUG_H */
