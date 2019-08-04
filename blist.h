#ifndef BLIST_BLIST_H
#define BLIST_BLIST_H

#include <iostream>

int blist_main(int argc, char **argv);

// Call as (for example)  std::cout << NL;
// Function: NL - Output a new line onto a stream.
inline std::ostream &NL(std::ostream &s) { return (s.put('\n')); }

// Function: FF - Output a form feed (new page) onto a stream.
inline std::ostream &FF(std::ostream &s) { return (s.put('\f')); }

#endif //BLIST_BLIST_H
