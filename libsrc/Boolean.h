#ifndef BOOLEAN_H
#define BOOLEAN_H

#ifdef __cplusplus
extern "C" {
#endif

// Contents ----------------------------------------------------------------
//
// Type Boolean
//
//	Contains the definitions for type BOOL, which represents truth values
//
// End ---------------------------------------------------------------------

/*
enum  _Bool  { FALSE, TRUE } Bool;
*/
#ifndef TRUE
#define TRUE 1
#define FALSE 0
#endif

typedef int  BOOL;
typedef int  Boolean;


inline  BOOL  Set ( BOOL& t )  { return (t=TRUE); };
inline  BOOL  Clear ( BOOL& t )  { return (t=FALSE); };

// Replace the value in a Boolean variable, and return the previous value.
inline  BOOL  Replace ( BOOL& t, const BOOL new_value )
{  BOOL  old = t;  t = new_value; return (old); };  


#ifdef __cplusplus
}
#endif

/****************************************************************************/
/* $Log$
/* Revision 1.3  1996/08/01 15:11:54  njt
/* Added conditional declarations for TRUE & FALSE now that the enum is not present
/*
 * Revision 1.1  91/02/09  17:49:00  njt
 * Initial revision
 *  */
/****************************************************************************/


#endif // ifndef BOOLEAN_H //
