/*  UTILMSG.C  */

#include <cstdio>
#include <cstdlib>
#include <string>

#include "proginfo.h"
#include "utilmsg.h"

const std::string ERROR_PREFIX = "**** ERROR";


/******************** START COMMENTED OUT SECTION ***********************/

/************************************************************************/
/* Use when a system call returns non-zero status.                      */
/*  TEXT should normally be the file name.                              */
/************************************************************************/
/*
void  perror_with_name( char *text )
{
  fprintf( stderr, "%s: ", ProgInfo::Name );
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
  fprintf( stderr, "%s: ", ProgInfo::Name );
  perror( text );
  exit( 2 );
}
*/

/******************* END COMMENTED OUT SECTION **************************/


/************************************************************************/
/* Print an error message.                                              */
/************************************************************************/

void error(const std::string& message) {
  const std::string& ProgName = ProgInfo::Name;

  fprintf(stderr, "\n%s: ", ProgName.c_str());
  fprintf(stderr, ERROR_PREFIX.c_str(), " ");
  fprintf(stderr, "%s", message.c_str());
  fprintf(stderr, "\n");
}

/************************************************************************/
/* Print an error message from the format-string FORMAT                 */
/*  with optional extra args as with printf.                            */
/************************************************************************/
/*
void error(const std::string &format, ...) {
  va_list args;

  va_start(args, format);

  fprintf(stderr, "\n%s: ", ProgInfo::Name.c_str());
  fprintf(stderr, ERROR_PREFIX.c_str(), " ");
  vfprintf(stderr, format.c_str(), args);
  fprintf(stderr, "\n");

  va_end(args);
}
*/
/************************************************************************/
/* Print an error message containing the string TEXT, then exit.        */
/************************************************************************/

void fatal(const std::string &message) {
/**************************
	print_message_queue();
**************************/
  // error(message);
  fprintf(stderr, "%s %s", ERROR_PREFIX.c_str(), message.c_str());
  fflush(stderr);  /* Probably not strictly necessary, but safest */
  exit(2);
}


/************************************************************************/
/* Like printf, except if paginate_flag is set                          */
/*      then save the message and print later.                          */
/************************************************************************/

void message(const std::string &format, const std::string &arg1, const std::string &arg2, ...) {
/*
  if (paginate_flag) {
    struct msg *
    new = (struct msg *) xmalloc(sizeof(struct msg));

    if (msg_chain_end == 0)
      msg_chain = msg_chain_end = new;
    else {
      msg_chain_end->next = new;
      msg_chain_end = new;
    }

    new->format = format;
    new->arg1 = concat(arg1, "", "");
    new->arg2 = concat(arg2, "", "");
    new->next = NULL;
  } else
*/
    printf(format.c_str(), arg1.c_str(), arg2.c_str());
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
/*
void *xmalloc(unsigned size) {
  register void *value;

  if (size == 0) {
    size = 1;
  }

  value = (void *) malloc(size);

  if (!value) {
    fatal("virtual memory exhausted");
  }

  return value;
}
*/

/************************************************************************/
/* realloc a block of memory,                                           */
/* with fatal error message if we can't do it.                          */
/************************************************************************/
/*
void *xrealloc(void *old, unsigned int size) {
  register void *value;

  if (size == 0) {
    size = 1;
  }

  value = (void *) realloc(old, size);

  if (!value) {
    fatal("virtual memory exhausted");
  }

  return value;
}
*/

/************************************************************************/
/* Concatenate three strings, returning a newly malloc'd string.        */
/************************************************************************/
/*
char *concat(char *s1, char *s2, char *s3) {
  int len = strlen(s1) + strlen(s2) + strlen(s3);

  char *
  new = (char *) xmalloc(len + 1);

  strcpy(new, s1);
  strcat(new, s2);
  strcat(new, s3);

  return new;
}
*/
