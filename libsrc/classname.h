#ifndef _CLASSNAME_H
#define _CLASSNAME_H

// Contents ----------------------------------------------------------------
//
//	Contains the class declaration for the Instance Counter classes
//		ClassName
//
// End ---------------------------------------------------------------------


// Interface Dependencies --------------------------------------------------
// None
// End Interface Dependencies ----------------------------------------------


// Description -------------------------------------------------------------
//
// class ClassName
// ===============
//
//	Record classname details.
//
// Constructor: ClassName
//
// Destructor: ~ClassName
//
// Member functions:
//
// Stream output function
//	None.
//
// Inherited Members
//	None.
//
// Private Members
//	None.
//
// Protected Members
//	szClass
//		The name of the class.
//
// End ---------------------------------------------------------------------
class ClassName
{
private:
	const char *	szClass;
public:
	ClassName( const char * clname ) : szClass( clname )  { };
	~ClassName()  { };
	const char * Class( ) const  { return szClass; };
};
// End of class ClassName


/******************************************************************************
 Change History
 ==============

Date          | Name  | Description
--------------+-------+-------------------------------------------------------
30-Jul-96	NJT	v1.1 - Initial UNIX version under SCCS control.
******************************************************************************/

#endif /* ifndef _CLASSNAME_H */
/* EOF */
