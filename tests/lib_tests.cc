#include "gtest/gtest.h"

#include "../libsrc/proginfo.h"
#include "../libsrc/utildbug.h"
#include "../libsrc/File.h"
#include "../libsrc/FileName.h"
#include "../libsrc/TextBox.h"

#define DEBUG

TEST(lib_tests, File) {
  TraceEntryExit t("lib_tests", "File test");

  std::cout << "Start File test" << std::endl;

  File file("cmake_install.cmake");
  File none("nofile.non", false);  // Non-existent file

  EXPECT_TRUE(file.Exists()) << file.to_string() << " should exist.";
  EXPECT_FALSE(none.Exists()) << none.to_string() << " should not exist.";

  std::cout << file.FullName() << std::endl << file << std::endl;

  std::cout << none.FName() << std::endl << none << std::endl;

  std::cout << "End File test" << std::endl;
}

TEST(lib_tests, FileName_Exists) {
  TraceEntryExit t("lib_tests", "FileName_Exists test");

  std::cout << "Start FileName test" << std::endl;

  FileName file("cmake_install.cmake");
  FileName none("nofile.non");  // Non-existent file

  std::cout << "file : " << file << " Exists = " << file.Exists() << std::endl;
  EXPECT_TRUE(file.Exists()) << file.to_string() << " should exist.";

  std::cout << "none : " << none << " Exists = " << none.Exists() << std::endl;
  EXPECT_FALSE(none.Exists()) << none.to_string() << " should not exist.";

  file = PathName(file);
  std::cout << "path(file) : " << file << " Exists = " << file.Exists() << std::endl;
  EXPECT_TRUE(file.Exists()) << file.to_string() << " should exist.";

  std::cout << "End FileName test" << std::endl;
}

TEST(lib_tests, PathName_Split) {
  TraceEntryExit t("lib_tests", "PathName_Split test");

  auto current_dir = PathName::GetCurrentDirectory();

  std::string file_name = "./FileName.cc";

  auto file_path = PathName(file_name);
  EXPECT_EQ(file_path.FName(), "FileName.cc");
  EXPECT_EQ(file_path.DirName(), current_dir);
}

TEST(lib_tests, TextBox) {
  TraceEntryExit t("lib_tests", "TextBox test");

  std::vector<std::string> multi_line = { "Line1", "Line2", "Line3", "Last Line" };

  std::cout << "Start TextBox test" << std::endl;

  std::cout << TextBox ( "Text in a box" );

  std::cout << TextBox ( "More text in a box", TextBox::STANDARD );

  std::cout << TextBox ( "Even more text in an X-box", TextBox::DOUBLE, 'X' );

  std::cout << TextBox ( multi_line, TextBox::STANDARD );

  std::cout << "End TextBox test" << std::endl;
}
