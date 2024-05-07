#include <cstdint>
#include <cstdio>
#include <cstring>  // For function strchr

#include "getopt.h"

// Based on: https://stackoverflow.com/questions/10404448/getopt-h-compiling-linux-c-code-in-windows

int opt_err = 1; /* if error message should be printed */
int opt_ind = 1; /* index into parent argv vector */
int opt_opt;     /* character checked for validity */
int opt_reset;   /* reset getopt */

char* opt_arg; /* argument associated with option */

static constexpr int BAD_CHAR = '?';
static constexpr int BAD_ARG  = ':';

static constexpr const char* BLANK_MSG = "";

/*
* getopt --
*      Parse argc/argv argument vector.
*/
int getopt(const int argc, char* const argv[], const char* ostr)
{
  /* option letter processing */
  static char* place = const_cast<char*>(BLANK_MSG);

  /* option letter list index */
  const char* oli;

  if (opt_reset || !*place) {
    /* update scanning pointer */
    opt_reset = 0;
    if (opt_ind >= argc || *(place = argv[opt_ind]) != '-') {
      place = const_cast<char*>(BLANK_MSG);
      return -1;
    }
    if (place[1] && *++place == '-') {
      /* found "--" */
      ++opt_ind;
      place = const_cast<char*>(BLANK_MSG);
      return -1;
    }
  }
  /* option letter okay? */
  if ((opt_opt = static_cast<std::uint8_t>(*place++)) == static_cast<std::uint8_t>(':')
      || !(oli = strchr(ostr, opt_opt))) {
    /* if the user didn't specify '-' as an option, assume it means -1. */
    if (opt_opt == static_cast<int>('-')) {
      return -1;
    }
    if (!*place) {
      ++opt_ind;
    }
    if (opt_err && *ostr != ':') {
      (void) printf("illegal option -- %c\n", opt_opt);
    }
    return BAD_CHAR;
  }
  if (*++oli != ':') {
    /* don't need argument */
    opt_arg = nullptr;
    if (!*place) {
      ++opt_ind;
    }
  }
  else {
    /* need an argument */
    if (*place) {
      /* no white space */
      opt_arg = place;
    }
    else if (argc <= ++opt_ind) {
      /* no arg */
      place = const_cast<char*>(BLANK_MSG);
      if (*ostr == ':') {
        return BAD_ARG;
      }
      if (opt_err) {
        (void) printf("option requires an argument -- %c\n", opt_opt);
      }
      return BAD_CHAR;
    }
    else {
      /* white space */
      opt_arg = argv[opt_ind];
    }
    place = const_cast<char*>(BLANK_MSG);
    ++opt_ind;
  }
  return opt_opt; /* dump back option letter */
}
