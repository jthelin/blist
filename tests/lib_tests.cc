#if defined(__clang__)
#pragma clang diagnostic push
#pragma ide diagnostic   ignored "cert-err58-cpp"
#endif

#include "gtest/gtest.h"

#include "../libsrc/File.h"
#include "../libsrc/TextBox.h"
#include "../libsrc/TraceEntryExit.h"
#include "../libsrc/fileutil.h"

#define DEBUG

static const std::string prog_name = "file_filter_tests";

TEST(lib_tests, TraceLevelOverride)
{
  TraceEntryExit t(prog_name, "TraceLevelOverride", true);

  // Begin scope #1
  {
    auto trace_override = TraceLevelOverride::SetLogging(true);

    TraceEntryExit t1(prog_name, "TraceEntryExit_test_on");
  }
  // End scope #1

  // Begin scope #2
  {
    auto trace_override = TraceLevelOverride::SetLogging(false);

    TraceEntryExit t2(prog_name, "TraceEntryExit_test_off");
  }
  // End scope #2
}

TEST(lib_tests, File_Exists)
{
  TraceEntryExit t(prog_name, "File_Exists", true);

  auto file = File("no-file.non", false); // Non-existent file
  EXPECT_FALSE(file.Exists()) << file.FullName() << " should not exist.";
  EXPECT_FALSE(FileUtils::IsFileReadable(file.FullName())) << file.FullName() << " should be readable.";

  file = File("cmake_install.cmake");
  EXPECT_TRUE(file.Exists()) << file.FullName() << " should exist.";
  EXPECT_TRUE(FileUtils::IsFileReadable(file.FullName())) << file.FullName() << " should be readable.";
}

TEST(lib_tests, File_PrintTo)
{
  TraceEntryExit t(prog_name, "File_PrintTo", true);

  auto none = File("no-file.non", false); // Non-existent file
  EXPECT_FALSE(none.Exists()) << none.FullName() << " should not exist.";
  std::cout << none.FullName() << std::endl << none << std::endl;

  auto file = File("cmake_install.cmake");
  EXPECT_TRUE(file.Exists()) << file.FullName() << " should exist.";
  std::cout << file.FullName() << std::endl << file << std::endl;
}

TEST(lib_tests, TextBox)
{
  TraceEntryExit t(prog_name, "TextBox", true);

  const std::vector<std::string> multi_line = {"Multiple lines", "Line1", "Line2", "Line3", "Last Line"};

  std::cout << TextBox("Text in a box", TextBox::BASIC);

  std::cout << TextBox("More text in a bigger box", TextBox::STANDARD);

  std::cout << TextBox("Even more text in an X-box", TextBox::DOUBLE, 'X');

  std::cout << TextBox(multi_line, TextBox::STANDARD);
}

TEST(lib_tests, file_utils_basename)
{
  EXPECT_EQ(FileUtils::basename(""), "");
  EXPECT_EQ(FileUtils::basename("no_path"), "no_path");
  EXPECT_EQ(FileUtils::basename("with.ext"), "with.ext");
  EXPECT_EQ(FileUtils::basename("/no_filename/"), "");
  EXPECT_EQ(FileUtils::basename("no_filename/"), "");
  EXPECT_EQ(FileUtils::basename("/no/filename/"), "");
  EXPECT_EQ(FileUtils::basename("/absolute/file.ext"), "file.ext");
  EXPECT_EQ(FileUtils::basename("../relative/file.ext"), "file.ext");
  EXPECT_EQ(FileUtils::basename("/"), "");
#if defined(_WIN32)
  EXPECT_EQ(FileUtils::basename("c:\\windows\\path.ext"), "path.ext");
  EXPECT_EQ(FileUtils::basename("c:\\windows\\no_filename\\"), "no_filename");
#endif
}

TEST(lib_tests, file_utils_dirname)
{
  EXPECT_EQ(FileUtils::dirname(""), ".");
  EXPECT_EQ(FileUtils::dirname("no_path"), ".");
  EXPECT_EQ(FileUtils::dirname("with.ext"), ".");
  EXPECT_EQ(FileUtils::dirname("/no_filename/"), "/no_filename/");
  EXPECT_EQ(FileUtils::dirname("no_filename/"), "no_filename/");
  EXPECT_EQ(FileUtils::dirname("/no/filename/"), "/no/filename/");
  EXPECT_EQ(FileUtils::dirname("/absolute/file.ext"), "/absolute/");
  EXPECT_EQ(FileUtils::dirname("../relative/file.ext"), "../relative/");
  EXPECT_EQ(FileUtils::dirname("/"), "/");
#if defined(_WIN32)
  EXPECT_EQ(FileUtils::dirname("c:\\windows\\path.ext"), "c:\\windows");
  EXPECT_EQ(FileUtils::dirname("c:\\windows\\no_filename\\"), "c:\\windows\\no_filename");
#endif
}

#if defined(__clang__)
#pragma clang diagnostic pop
#endif
