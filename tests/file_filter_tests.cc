#if defined(__clang__)
#pragma clang diagnostic push
#pragma ide diagnostic   ignored "cert-err58-cpp"
#endif

#include "gtest/gtest.h"

#include <fstream>

#include "../libsrc/File.h"
#include "../libsrc/TraceEntryExit.h"
#include "../libsrc/filter.h"

static const std::string prog_name = "file_filter_tests";

TEST(file_filter_tests, ReadLines)
{
  TraceEntryExit t(prog_name, "ReadLines", true);

  auto file = File("cmake_install.cmake");
  EXPECT_TRUE(file.Exists()) << file.FullName() << " should exist.";

  auto file_reader = std::ifstream(file.FullName());
  auto counter     = std::make_unique<LineCounter>(file_reader);

  int rc = counter->main_loop();

  std::cout << counter->result() << " lines read." << std::endl;

  EXPECT_GE(counter->result(), 10) << "Should have read some records.";
  EXPECT_NE(rc, 0) << "Should not have got zero result code.";
}

TEST(file_filter_tests, ReadChars)
{
  TraceEntryExit t(prog_name, "ReadChars", true);

  auto file = File("cmake_install.cmake");
  EXPECT_TRUE(file.Exists()) << file.FullName() << " should exist.";

  auto file_reader = std::ifstream(file.FullName());
  auto counter     = std::make_unique<CharCounter>(file_reader);

  int rc = counter->main_loop();

  std::cout << counter->result() << " characters read." << std::endl;

  EXPECT_GE(counter->result(), 1000) << "Should have read some data.";
  EXPECT_NE(rc, 0) << "Should not have got zero result code.";
}

#if defined(__clang__)
#pragma clang diagnostic pop
#endif
