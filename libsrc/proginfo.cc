#ifndef lint
static char ident_proginfo_c[]="%Z% $RCSfile$  v$Revision$  $Date$__ - njt";
#endif /* lint */

/*******************************************************************************
*
* File		:	proginfo.h
*
* Authors	:	Jorgen Thelin
* 
* Abstract	:	Program information and sign-on.
*    
* Environment   :	NCR UNIX V.4
*
* Change History:	See bottom of file.
*  
******************************************************************************/

/* include files */

#include <stdio.h>

#include <proginfo.h>


/******************************************************************************
* Function:	ProgramSignOn
*
* Purpose:	Output sign-on message to stderr, based on the contents of the
		variables ProgName, ProgVer, ProgRelStat ProgAuthor which
		should be defined by the main program.
******************************************************************************/
void ProgramSignOn( void )
{
	ModuleSignOn(
		ProgName,
		ProgVer,
		ProgRelStat,
		ProgAuthor );
}

/******************************************************************************
* Function:	ModuleSignOn
*
* Purpose:	Output sign-on message to stderr, based on the contents of the
		parameters szProgName, szProgVer, szProgRelStat szProgAuthor.
******************************************************************************/
void ModuleSignOn( 
	const char *	szProgName,
	const char *    szProgVer,
	const char *    szProgRelStat,
	const char *    szProgAuthor )
{
	fprintf(stderr,
		"%s  v%s.[%s]  (%s)\n",
		szProgName,
		szProgVer,
		szProgRelStat,
		szProgAuthor );
}

/* EOF */
