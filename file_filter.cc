
#include "libsrc/filter.h"

#include <filesystem>
#include <fstream>

static constexpr std::string_view prog_name = "file_filter";

static int filter_file(const std::filesystem::path& input_file, bool count_lines = true)
{
  std::string   source;
  std::istream* p_input_stream;
  std::ifstream ifs;
  if (input_file.empty()) {
    p_input_stream = &(std::cin);
    source         = "stdin stream";
  }
  else {
    const std::string file_name = input_file.generic_string();
    if (!std::filesystem::exists(input_file)) {
      std::cerr << prog_name << ": ERROR: Input file not found '" << file_name << "'." << std::endl;
      return -1;
    }
    ifs            = std::ifstream(input_file);
    p_input_stream = &ifs;
    source         = std::string("file '" + file_name + "'");
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

  auto count = counter->main_loop();

  std::cout.flush();

  if (count_lines) {
    auto num_lines = counter->result();
    std::cout << "Read " << num_lines << " lines from " << source << std::endl;
  }
  else {
    auto num_chars = counter->result();
    std::cout << "Read " << num_chars << " chars from " << source << std::endl;
  }

  std::cerr << "Main loop completed with count = " << count << std::endl;

  return count;
}

static int file_filter_main(int argc, char** argv)
{
  std::filesystem::path input_file;
  bool                  count_lines = true; // Temp HACK

  if (argc >= 1) {
    input_file = argv[1];
  }

  auto num_lines = filter_file(input_file, count_lines);

  return num_lines > 0 ? 0 : num_lines;
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
