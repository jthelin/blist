
#include "libsrc/filter.h"
#include "libsrc/FilePath.h"

#include <exception>
#include <fstream>
#include <iostream>
#include <memory>

std::string prog_name = "file_filter";

int file_filter_main(int argc, char **argv) {
  bool count_lines = true; // Temp HACK
  std::string source;
  std::istream *p_input_stream;
  if (argc < 1) {
    p_input_stream = &(std::cin);
    source = "stdin stream";
  } else {
	const std::string file_name = argv[1];
    const FilePath input_file(file_name);
    if (!input_file.Exists()) {
      std::cerr << prog_name << ": ERROR: Input file not found '" << input_file.FullName() << "'." << std::endl;
      return -1;
    }
    p_input_stream = std::make_unique<std::ifstream>(input_file.FullName()).get();
    source = "file '" + input_file.FullName() + "'";
  }

  std::unique_ptr<IFilter> counter;
  if (count_lines) {
    std::cerr <<  prog_name << ": Reading from " << source << " and count lines." << std::endl;
    counter = std::make_unique<LineCounter>(*p_input_stream);
  } else {
    std::cerr <<  prog_name << ": Reading from " << source << " and count characters." << std::endl;
    counter = std::make_unique<CharCounter>(*p_input_stream);
  }
  std::cerr.flush();
  std::cout.flush();

  const int rc = counter->main_loop();

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

int main(int argc, char *argv[]) {
  int rc = -1;
#ifndef _LIBCPP_NO_EXCEPTIONS
  try {
#endif
    rc = file_filter_main(argc, argv);
#ifndef _LIBCPP_NO_EXCEPTIONS
  }
  catch (std::exception& e)
  {
    std::cerr << prog_name << ": ERROR:"
              << " Exception thrown during program execution."
              << " " << e.what()
              << std::endl;
  }
#endif
  return rc;
}
