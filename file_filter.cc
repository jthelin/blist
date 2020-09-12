
#include "libsrc/filter.h"

#include <exception>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>

static constexpr std::string_view prog_name = "file_filter";

int filter_file(const std::filesystem::path& input_file, bool count_lines = true)
{
  std::string   source;
  std::istream* p_input_stream;
  std::ifstream ifs;
  if (input_file.empty()) {
    p_input_stream = &(std::cin);
    source         = "stdin stream";
  }
  else {
    if (!std::filesystem::exists(input_file)) {
      std::cerr << prog_name << ": ERROR: Input file not found '" << input_file.generic_string() << "'." << std::endl;
      return -1;
    }
    ifs = std::ifstream(input_file);
    p_input_stream = &ifs;
    source         = "file '" + input_file.generic_string() + "'";
  }

  std::unique_ptr<IFilter> counter;
  if (count_lines) {
    std::cerr << prog_name << ": Reading from " << source << " and count lines." << std::endl;
    counter = std::make_unique<LineCounter>(*p_input_stream);
  }
  else {
    std::cerr << prog_name << ": Reading from " << source << " and count characters." << std::endl;
    counter = std::make_unique<CharCounter>(*p_input_stream);
  }
  std::cerr.flush();
  std::cout.flush();

  const int rc = counter->main_loop();

  std::cout.flush();

  if (count_lines) {
    std::cout << "Read " << counter->result() << " lines from " << source << std::endl;
  }
  else {
    std::cout << "Read " << counter->result() << " chars from " << source << std::endl;
  }

  std::cerr << "Main loop completed with rc = " << rc << std::endl;

  return rc;
}

int file_filter_main(int argc, char** argv)
{
  std::filesystem::path input_file;
  bool                  count_lines = true; // Temp HACK

  if (argc >= 1) {
    input_file = argv[1];
  }

  return filter_file(input_file, count_lines);
} // End function file_filter_main

int main(int argc, char* argv[])
{
  int rc = -1;
  try {
    rc = file_filter_main(argc, argv);
  }
  catch (std::exception& e) {
    std::cerr << prog_name << ": ERROR:"
              << " Exception thrown during program execution."
              << " " << e.what() << std::endl;
  }
  return rc;
} // End function main
