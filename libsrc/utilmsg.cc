/*  UTILMSG.C  */


#include "utilmsg.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


extern char program[];   /* Program name - usually defined in main module */


#define ERROR_PREFIX  "**** ERROR"


/******************** START COMMENTED OUT SECTION ***********************/

/************************************************************************/
/* Use when a system call returns non-zero status.                      */
/*  TEXT should normally be the file name.                              */
/************************************************************************/
/*
void  perror_with_name( char *text )
{
  fprintf( stderr, "%s: ", program );
  perror( text );
}
*/

/************************************************************************/
/* Use when a system call returns non-zero status and that is fatal.    */
/************************************************************************/
/*
void  pfatal_with_name( char *text )
{
  print_message_queue();
  fprintf( stderr, "%s: ", program );
  perror( text );
  exit( 2 );
}
*/

/******************* END COMMENTED OUT SECTION **************************/



/************************************************************************/
/* Print an error message from the format-string FORMAT                 */
/*  with optional extra args as with printf.                            */
/************************************************************************/
/*
void  error( char *format, ... )
{
 va_list  args;

  va_start(args,format);

  fprintf( stderr, "\n%s: ", program);
    fprintf( stderr, ERROR_PREFIX " " );
    vfprintf( stderr, format, args);
        fprintf( stderr, "\n");

 va_end(args);
}
*/

/************************************************************************/
/* Print an error message containing the string TEXT, then exit.        */
/************************************************************************/

void  fatal( char *message )
{
/**************************
	print_message_queue();
**************************/
/*	error( message, "" ); */
	fprintf( stderr, message );
	fflush( stderr );  /* Probably not strictly necessary, but safest */
	exit( 2 );
}



/************************************************************************/
/* Like printf, except if paginate_flag is set                          */
/*      then save the message and print later.                          */
/************************************************************************/

void  message( char *format, char *arg1, char *arg2, ... )
{

/*

       if (paginate_flag) {

            struct msg *new = (struct msg *) xmalloc (sizeof (struct msg));

         if (msg_chain_end == 0)
                 msg_chain = msg_chain_end = new;
                else {
                  msg_chain_end->next = new;
                      msg_chain_end = new;
            }

               new->format = format;
           new->arg1 = concat( arg1, "", "" );
             new->arg2 = concat( arg2, "", "" );
             new->next = NULL;
       } else

*/

                printf (format, arg1, arg2);
}


/******************** START COMMENTED OUT SECTION ***********************/

/************************************************************************/
/* Output all the messages that were saved up by calls to `message'.    */
/************************************************************************/
/*
void  print_message_queue( void )
{
  struct msg *m;

  for (m = msg_chain; m; m = m->next)
           printf (m->format, m->arg1, m->arg2);
}
*/
/******************* END COMMENTED OUT SECTION **************************/



/************************************************************************/
/* malloc a block of memory,                                            */
/* with fatal error message if we can't do it.                          */
/************************************************************************/

void *xmalloc ( unsigned size )
{
    register void *value;

   if (size == 0)
          size = 1;

       value = (void *) malloc(size);

  if (!value)
             fatal( "virtual memory exhausted" );

    return value;
}


/************************************************************************/
/* realloc a block of memory,                                           */
/* with fatal error message if we can't do it.                          */
/************************************************************************/

void *xrealloc( void *old, unsigned int size )
{
     register void *value;

   if (size == 0)
          size = 1;

       value = (void *) realloc( old, size );

  if (!value)
             fatal ("virtual memory exhausted");

     return value;
}


/************************************************************************/
/* Concatenate three strings, returning a newly malloc'd string.        */
/************************************************************************/

char *concat( char *s1, char *s2, char *s3)
{
  int len = strlen(s1) + strlen(s2) + strlen(s3);

  char *new = (char *) xmalloc( len + 1 );

  strcpy (new, s1);
  strcat (new, s2);
  strcat (new, s3);

  return new;
}

