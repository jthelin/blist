#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err58-cpp"

#include "gtest/gtest.h"

#include "../libsrc/proginfo.h"
#include "../libsrc/File.h"
#include "../libsrc/FileName.h"
#include "../libsrc/TextBox.h"
#include "../libsrc/TraceEntryExit.h"

#define DEBUG

TEST(lib_tests, TraceLevelOverride) {
  {
    auto trace_override = TraceLevelOverride::SetLogging(true);
    TraceEntryExit t("lib_tests", "TraceEntryExit_test_on");
  }

  {
    auto trace_override = TraceLevelOverride::SetLogging(false);
    TraceEntryExit t("lib_tests", "TraceEntryExit_test_off");
  }
}

TEST(lib_tests, File) {
  TraceEntryExit t("lib_tests", "File", true);

  File file("cmake_install.cmake");
  File none("no-file.non", false);  // Non-existent file

  EXPECT_TRUE(file.Exists()) << file.to_string() << " should exist.";
  EXPECT_FALSE(none.Exists()) << none.to_string() << " should not exist.";

  std::cout << file.FullName() << std::endl << file << std::endl;

  std::cout << none.FName() << std::endl << none << std::endl;
}

TEST(lib_tests, FilePath_Exists) {
  TraceEntryExit t("lib_tests", "FilePath_Exists", true);

  FileName none("no-file.non");  // Non-existent file
  std::cout << "none : " << none << " Exists = " << none.Exists() << std::endl;
  EXPECT_FALSE(none.Exists()) << none.to_string() << " should not exist.";

  FileName file("cmake_install.cmake");
  std::cout << "file : " << file << " Exists = " << file.Exists() << std::endl;
  EXPECT_TRUE(file.Exists()) << file.to_string() << " should exist.";
}

TEST(lib_tests, FilePath_Path_Split) {
  TraceEntryExit t("lib_tests", "FilePath_Path_Split", true);

  auto current_dir = PathName::GetCurrentDirectory();

  std::string file_name = "./FileName.cc";

  auto file_path = PathName(file_name);
  EXPECT_EQ(file_path.FName(), "FileName.cc");
  EXPECT_EQ(file_path.DirName(), current_dir);
}

TEST(lib_tests, TextBox) {
  TraceEntryExit t("lib_tests", "TextBox", true);

  std::vector<std::string> multi_line = {"Line1", "Line2", "Line3", "Last Line"};

  std::cout << TextBox("Text in a box");

  std::cout << TextBox("More text in a box", TextBox::STANDARD);

  std::cout << TextBox("Even more text in an X-box", TextBox::DOUBLE, 'X');

  std::cout << TextBox(multi_line, TextBox::STANDARD);
}

#pragma clang diagnostic pop
