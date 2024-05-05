#pragma once

#include <iostream>
#include <string>
#include <vector>

struct blist_params {
  constexpr static int DEF_TAB_SIZE = 4;

  bool _debug = false;

  bool useFormFeed = false;

  int tab_size = DEF_TAB_SIZE;

  bool flush = true;

  std::vector<std::string> files{};
};

int blist_main(int argc, char** argv);

// Call as (for example)  std::cout << NL;
// Function: NL - Output a new line onto a stream.
inline std::ostream& NL(std::ostream& s) {
  return s.put('\n');
}

// Function: FF - Output a form feed (new page) onto a stream.
inline std::ostream& FF(std::ostream& s) {
  return s.put('\f');
}
