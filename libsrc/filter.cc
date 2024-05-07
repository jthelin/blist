// _LIBCPP_NO_EXCEPTIONS will be defined if the C++ compiler does not support Exceptions.

#include "filter.h"

/**
 * Function main_loop (using Exceptions unless _LIBCPP_NO_EXCEPTIONS is defined)
 * @return
 */
int IFilter::main_loop()
{
  IFilter* p = this;

  for (;;) // Loop forever, until breakout condition is hit.
  {
    try {
      p->start();
      while (p->read()) {
        p->compute();
        p->write();
      }
      return p->result(); // Exit loop
    }
    catch (IFilter::ERetry& m) {
      std::cerr << m.message() << std::endl;
      int i = p->retry();
      if (i) {
        return -i; // Exit loop
      }
    }
    catch (...) {
      std::cerr << "ERROR: Fatal filter error" << std::endl;
      return -10; // Exit loop
    }
  } // End forever loop

  // Not reached.
}
