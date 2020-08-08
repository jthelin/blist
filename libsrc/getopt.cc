#include <cstdio>
#include <cstring>

#include "getopt.h"

// Based on: https://stackoverflow.com/questions/10404448/getopt-h-compiling-linux-c-code-in-windows

int opterr = 1, /* if error message should be printed */
  optind   = 1, /* index into parent argv vector */
  optopt,       /* character checked for validity */
  optreset;     /* reset getopt */

char* optarg; /* argument associated with option */

constexpr int         BADCH     = '?';
constexpr int         BADARG    = ':';
constexpr const char* BLANK_MSG = "";

/*
* getopt --
*      Parse argc/argv argument vector.
*/
int getopt(int nargc, char* const nargv[], const char* ostr)
{
  /* option letter processing */
  static char* place = const_cast<char*>(BLANK_MSG);

  /* option letter list index */
  const char* oli;

  if (optreset || !*place) {
    /* update scanning pointer */
    optreset = 0;
    if (optind >= nargc || *(place = nargv[optind]) != '-') {
      place = const_cast<char*>(BLANK_MSG);
      return -1;
    }
    if (place[1] && *++place == '-') {
      /* found "--" */
      ++optind;
      place = const_cast<char*>(BLANK_MSG);
      return -1;
    }
  }
  /* option letter okay? */
  if ((optopt = static_cast<u_int8_t>(*place++)) == static_cast<u_int8_t>(':') || !((oli = strchr(ostr, optopt)))) {
    /* if the user didn't specify '-' as an option, assume it means -1. */
    if (optopt == static_cast<int>('-')) {
      return -1;
    }
    if (!*place) {
      ++optind;
    }
    if (opterr && *ostr != ':') {
      (void) printf("illegal option -- %c\n", optopt);
    }
    return BADCH;
  }
  if (*++oli != ':') {
    /* don't need argument */
    optarg = nullptr;
    if (!*place) {
      ++optind;
    }
  }
  else {
    /* need an argument */
    if (*place) {
      /* no white space */
      optarg = place;
    }
    else if (nargc <= ++optind) {
      /* no arg */
      place = const_cast<char*>(BLANK_MSG);
      if (*ostr == ':') {
        return BADARG;
      }
      if (opterr) {
        (void) printf("option requires an argument -- %c\n", optopt);
      }
      return BADCH;
    }
    else {
      /* white space */
      optarg = nargv[optind];
    }
    place = const_cast<char*>(BLANK_MSG);
    ++optind;
  }
  return optopt; /* dump back option letter */
}
