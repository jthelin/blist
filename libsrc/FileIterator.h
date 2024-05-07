#pragma once

// Contents ----------------------------------------------------------------
//
//    Contains the class declaration of the FileIterator Class
//
// End ---------------------------------------------------------------------

// Description -------------------------------------------------------------
//
// Class FileIterator
// ==================
//
//	Defines the file iterator class.  Upon initialization, we set up
//	an internal pointer to our current position in the file.  As
//	the increment operator is called, we update this current position.
//
// Constructor:	FileIterator( const File& toIterate )
//		FileIterator( const char * fileToIterate )
//	Constructor for an iterator - defines the file to iterate.
//	Either takes an existing File object, or creates a new File object from
//	the supplied filename
//
// Destructor:	~FileIterator
//
// Public Members:
//	operator char *
//		Conversion to char * operator
//		- returns pointer to the current line in the file as a C string.
//	more
//		Return FALSE when we have read (off the) end of the file.
//		For use in a standard for loop sequence.
//	next
//		Move on to the next line in the file.
//	operator int
//		Return false when we have read (off the) end of the file.
//		For use in a standard for loop sequence.
//	operator ++
//		The increment operator - move on to the next line in the file.
//	restart
//		Restarts a File iterator.
//		Not implemented yet.
//
// Private Members:
//	beingIterated
//		Maintains a pointer to the File being iterated.
//
// End ---------------------------------------------------------------------
/*
class FileIterator
{
private:
	BOOL		bFileObjCreated;
	File& 	 	beingIterated;
public:
			FileIterator( File& toIterate )
			:	bFileObjCreated( FALSE ),
				beingIterated( toIterate )
			{
				beingIterated.readRecord();  // Read 1st record
			};
			FileIterator( const char * fileToIterate )
			{
				beingIterated = new File(
					fileToIterate, TRUE ); // Log failures
			 	bFileObjCreated = TRUE;
				beingIterated.readRecord();  // Read 1st record
			};
	virtual		~FileIterator( void )
			{ if (bFileObjCreated) delete beingIterated; }

virtual BOOL	more( void )  const
{ return BOOL(!beingIterated.Eof()); };
virtual void	next( void )
{ beingIterated.readRecord(); };
virtual		operator char * ()  const
{ return beingIterated.getRecord(); };

//	virtual		operator int()  const  { return more(); };
//	virtual void	operator ++()  { next(); };
//
//	virtual void	restart();
};
*/
