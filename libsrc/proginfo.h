#ifndef _PROGINFO_H
#define _PROGINFO_H

#include <sys/cdefs.h>

__BEGIN_DECLS

#ident "%Z% $Id$__ - njt"

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

/* Program Information variables to be defined in the main program module */
extern char *	ProgName;	/* Program Name */
extern char *	ProgVer;	/* Program Version */
extern char *	ProgRelStat;	/* Program Release Status eg. Beta, Released */
extern char *	ProgAuthor;	/* Program Author */


extern void ProgramSignOn( void );

extern void ModuleSignOn(
		const char *	szProgName,
		const char *	szProgVer,
		const char *	szProgRelStat,
		const char *	szProgAuthor
);

#define	SIGNON	ProgramSignOn()

__END_DECLS

#endif _PROGINFO_H
/* EOF */
