
#include "libsrc/filter.h"
#include "libsrc/FilePath.h"

#include <fstream>
#include <iostream>
#include <memory>

class FileCharCounter : public ICharStreamFilter {
  int num_chars;
public:
  void compute() override { num_chars++; };

  int result() override {
    std::cout << num_chars << " characters read" << std::endl;
    return 0;
  };

  explicit FileCharCounter(std::istream &ii)
      : ICharStreamFilter(ii), num_chars(0) {}
};
// End class FileCharCounter

class FileLineCounter : public ILineStreamFilter {
  int num_lines;
public:
  void compute() override { num_lines++; };

  int result() override {
    std::cout << num_lines << " lines read" << std::endl;
    return 0;
  };

  explicit FileLineCounter(std::istream &ii)
      : ILineStreamFilter(ii), num_lines(0) {}
};
// End class FileLineCounter


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
      std::cerr << "test_filter: Input file not found '" << input_file.FullName() << "'." << std::endl;
      return -1;
    }
    p_input_stream = std::make_unique<std::ifstream>(file_name).get();
    source = "file '" + file_name + "'";
  }

  std::unique_ptr<IFilter> counter;
  if (count_lines) {
    std::cerr << "test_filter: Read from " << source << " and count lines." << std::endl;
    counter = std::make_unique<FileLineCounter>(*p_input_stream);
  } else {
    std::cerr << "test_filter: Read from " << source << " and count characters." << std::endl;
    counter = std::make_unique<FileCharCounter>(*p_input_stream);
  }
  std::cerr.flush();
  std::cout.flush();

  int rc = main_loop(counter.get());

  std::cout.flush();

  std::cerr << "Main loop completed with rc = " << rc << std::endl;

  return rc;
}
// End function main
