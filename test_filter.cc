
#include "libsrc/filter.h"

#include <fstream>
#include <ios>
#include <iostream>
#include <memory>

class MyCharFilter : public ICharStrmFilter {
  int num_chars;
public:
  void compute() override { num_chars++; };

  void write() override {};  // No output
  int result() override {
    std::cout << num_chars << " characters read\n";
    return 0;
  };

  explicit MyCharFilter(std::istream &ii)
      : ICharStrmFilter(ii), num_chars(0) {}
};
// End class MyCharFilter

class MyLineFilter : public ILineStrmFilter {
  int num_lines;
public:
  void compute() override { num_lines++; };

  void write() override {};  // No output
  int result() override {
    std::cout << num_lines << " lines read\n";
    return 0;
  };

  explicit MyLineFilter(std::istream &ii)
      : ILineStrmFilter(ii), num_lines(0) {}
};
// End class MyLineFilter


int main(int argc, char **argv) {
  std::istream *p_input_stream = nullptr;
  if (argc < 1) {
    p_input_stream = &(std::cin);
  } else {
    p_input_stream = std::make_unique<std::ifstream>( std::ifstream(argv[1]) ).get();
  }

  // std::cerr << "test_filter: Read from input stream and count characters.\n";
  // MyCharFilter f(*p_input_stream);

  std::cerr << "test_filter: Read from input stream and count lines.\n";
  MyLineFilter f(*p_input_stream);

  return main_loop(&f);
}
// End function main
