
#include "libsrc/filter.h"
#include "libsrc/FilePath.h"

#include <fstream>
#include <iostream>
#include <memory>

int main(int argc, char **argv) {
  bool count_lines = true;
  std::string source;
  std::istream *p_input_stream = nullptr;
  if (argc < 1) {
    p_input_stream = &(std::cin);
    source = "stdin stream";
  } else {
    std::string file_name = argv[1];
    FilePath input_file(file_name);
    if (!input_file.Exists()) {
      std::cerr << "test_filter: ERROR: Input file not found '" << input_file.FullName() << "'." << std::endl;
      return -1;
    }
    p_input_stream = std::make_unique<std::ifstream>(file_name).get();
    source = "file '" + file_name + "'";
  }

  std::unique_ptr<IFilter> counter;
  if (count_lines) {
    std::cerr << "test_filter: Reading from " << source << " and count lines." << std::endl;
    counter = std::make_unique<LineCounter>(*p_input_stream);
  } else {
    std::cerr << "test_filter: Reading from " << source << " and count characters." << std::endl;
    counter = std::make_unique<CharCounter>(*p_input_stream);
  }
  std::cerr.flush();
  std::cout.flush();

  int rc = counter->main_loop();

  std::cout.flush();

  if (count_lines) {
    std::cout << "Read " << counter->result() << " lines from " << source << std::endl;
  } else {
    std::cout << "Read " << counter->result() << " chars from " << source << std::endl;
  }

  std::cerr << "Main loop completed with rc = " << rc << std::endl;

  return rc;
}
// End function main
