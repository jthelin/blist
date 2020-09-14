#pragma once

extern int opt_err, /* if error message should be printed */
  opt_ind,          /* index into parent argv vector */
  opt_opt,          /* character checked for validity */
  opt_reset;        /* reset getopt */

extern char* opt_arg; /* argument associated with option */

/*
* getopt --
*      Parse argc/argv argument vector.
*/
extern int getopt(int argc, char* const argv[], const char* ostr);
