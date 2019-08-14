
#include "libsrc/filter.h"

#include <iostream>

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


int main() {

  // std::cerr << "test_filter: Read from cin stream and count characters.\n";
  // MyCharFilter f(std::cin);

  std::cerr << "test_filter: Read from cin stream and count lines.\n";
  MyLineFilter f(std::cin);

  return main_loop(&f);
};
// End function main
