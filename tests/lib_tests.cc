#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err58-cpp"

#include "gtest/gtest.h"

#include "../libsrc/proginfo.h"
#include "../libsrc/File.h"
#include "../libsrc/FilePath.h"
#include "../libsrc/TextBox.h"
#include "../libsrc/TraceEntryExit.h"

#define DEBUG

TEST(lib_tests, TraceLevelOverride) {
  TraceEntryExit t("lib_tests", "TraceLevelOverride", true);

  // Begin scope #1
  {
    auto trace_override = TraceLevelOverride::SetLogging(true);
    TraceEntryExit t("lib_tests", "TraceEntryExit_test_on");
  }
  // End scope #1

  // Begin scope #2
  {
    auto trace_override = TraceLevelOverride::SetLogging(false);
    TraceEntryExit t("lib_tests", "TraceEntryExit_test_off");
  }
  // End scope #2
}

TEST(lib_tests, File) {
  TraceEntryExit t("lib_tests", "File", true);

  File none("no-file.non", false);  // Non-existent file
  EXPECT_FALSE(none.Exists()) << none.to_string() << " should not exist.";
  std::cout << none.FName() << std::endl << none << std::endl;

  File file("cmake_install.cmake");
  EXPECT_TRUE(file.Exists()) << file.to_string() << " should exist.";
  std::cout << file.FullName() << std::endl << file << std::endl;
}

TEST(lib_tests, FilePath_Exists) {
  TraceEntryExit t("lib_tests", "FilePath_Exists", true);

  FilePath none("no-file.non");  // Non-existent file
  std::cout << "none : " << none << " Exists = " << none.Exists() << std::endl;
  EXPECT_FALSE(none.Exists()) << none.to_string() << " should not exist.";

  FilePath file("cmake_install.cmake");
  std::cout << "file : " << file << " Exists = " << file.Exists() << std::endl;
  EXPECT_TRUE(file.Exists()) << file.to_string() << " should exist.";
}

TEST(lib_tests, FilePath_Split) {
  TraceEntryExit t("lib_tests", "FilePath_Split", true);

  auto current_dir = FilePath::GetCurrentDirectory();

  std::string file_name = "./FileName.cc";

  auto file_path = FilePath(file_name);
  EXPECT_EQ(file_path.FName(), "FileName.cc");
  EXPECT_EQ(file_path.DirName(), current_dir);
}

TEST(lib_tests, FilePath_Absolute) {
  TraceEntryExit t("lib_tests", "FilePath_Absolute", true);

  auto current_dir = FilePath::GetCurrentDirectory();
  std::cout << "Current directory = " << current_dir << std::endl;

  std::string file_name = current_dir + "/FileName.cc";
  std::cout << "File = " << file_name << std::endl;

  auto file_path = FilePath(file_name);
  EXPECT_EQ(file_path.FName(), "FileName.cc");
  EXPECT_EQ(file_path.DirName(), current_dir);
}

TEST(lib_tests, TextBox) {
  TraceEntryExit t("lib_tests", "TextBox", true);

  std::vector<std::string> multi_line = {"Multiple lines", "Line1", "Line2", "Line3", "Last Line"};

  std::cout << TextBox("Text in a box", TextBox::BASIC);

  std::cout << TextBox("More text in a bigger box", TextBox::STANDARD);

  std::cout << TextBox("Even more text in an X-box", TextBox::DOUBLE, 'X');

  std::cout << TextBox(multi_line, TextBox::STANDARD);
}

#pragma clang diagnostic pop
