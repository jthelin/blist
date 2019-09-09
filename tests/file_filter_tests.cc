#if defined(__clang__)
#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err58-cpp"
#endif

#include "gtest/gtest.h"

#include <iostream>
#include <fstream>

#include "../libsrc/filter.h"
#include "../libsrc/FilePath.h"
#include "../libsrc/TraceEntryExit.h"

TEST(file_filter_tests, ReadLines) {
  TraceEntryExit t("file_filter_tests", "ReadLines", true);

  FilePath file("cmake_install.cmake");
  EXPECT_TRUE(file.Exists()) << file.to_string() << " should exist.";

  auto file_reader = std::make_unique<std::ifstream>(file.FullName());
  auto counter = std::make_unique<LineCounter>(*file_reader);

  int rc = counter->main_loop();

  std::cout << counter->result() << " lines read." << std::endl;

  EXPECT_GE(counter->result(), 10) << "Should have read some records.";
  EXPECT_NE(rc, 0) << "Should not have got zero result code.";
}

TEST(file_filter_tests, ReadChars) {
  TraceEntryExit t("file_filter_tests", "ReadChars", true);

  FilePath file("cmake_install.cmake");
  EXPECT_TRUE(file.Exists()) << file.to_string() << " should exist.";

  auto file_reader = std::make_unique<std::ifstream>(file.FullName());
  auto counter = std::make_unique<CharCounter>(*file_reader);

  int rc = counter->main_loop();

  std::cout << counter->result() << " characters read." << std::endl;

  EXPECT_GE(counter->result(), 1000) << "Should have read some data.";
  EXPECT_NE(rc, 0) << "Should not have got zero result code.";
}

#if defined(__clang__)
#pragma clang diagnostic pop
#endif
