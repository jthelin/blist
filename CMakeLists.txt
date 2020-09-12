CMAKE_MINIMUM_REQUIRED(VERSION 3.16)

PROJECT(blist
        VERSION 2.1.0
        DESCRIPTION "Bulk list contents of text file(s) to stdout (for redirection), preceded by a header block with file info"
        HOMEPAGE_URL "https://github.com/jthelin/blist"
        LANGUAGES CXX
        )
set(PROJECT_AUTHOR "J.Thelin")
set(PROJECT_STATUS "")

SET(CMAKE_CXX_STANDARD 17)

set(LIB_NAME ${PROJECT_NAME}_lib)

INCLUDE(GNUInstallDirs)

string(TIMESTAMP BUILD_DATE "%Y-%m-%d")
string(TIMESTAMP BUILD_TIMESTAMP "%Y-%m-%d_%H:%M:%S")

# Google Test Framework
include(cmake/googletest.cmake)

# Cmake Modules
include(cmake/cmake-modules.cmake)

# Application

# Burn version info into app header file.
CONFIGURE_FILE(
        ${PROJECT_SOURCE_DIR}/${PROJECT_NAME}_version.h.in
        ${PROJECT_SOURCE_DIR}/${PROJECT_NAME}_version.h)

FILE(GLOB lib_SRCS CONFIGURE_DEPENDS "libsrc/*.cc")
FILE(GLOB lib_HDRS CONFIGURE_DEPENDS "libsrc/*.h")

SET(blist_SRCS blist.cc blist.h ${PROJECT_NAME}_version.h)

ADD_LIBRARY(${LIB_NAME} STATIC ${lib_HDRS} ${lib_SRCS})

ADD_EXECUTABLE(${PROJECT_NAME} ${blist_SRCS} ${lib_HDRS})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${LIB_NAME})

ADD_EXECUTABLE(file_filter
        file_filter.cc
        ${lib_HDRS})
TARGET_LINK_LIBRARIES(file_filter ${LIB_NAME})

include(CppcheckTargets)
add_cppcheck(${PROJECT_NAME} UNUSED_FUNCTIONS STYLE POSSIBLE_ERROR FAIL_ON_WARNINGS)
add_cppcheck(file_filter UNUSED_FUNCTIONS STYLE POSSIBLE_ERROR FAIL_ON_WARNINGS)

# Enable Address Sanitizer in Debug builds
if (NOT(WIN32))
    string(APPEND CMAKE_CXX_FLAGS_DEBUG " -fsanitize=address")
    string(APPEND CMAKE_LINKER_FLAGS_DEBUG " -fsanitize=address")
endif()

# Testing

ENABLE_TESTING()

FILE(GLOB test_SRCS CONFIGURE_DEPENDS "tests/*.cc")

# Now simply link against gtest or gtest_main as needed.
ADD_EXECUTABLE(blist_test ${test_SRCS} ${lib_HDRS})
TARGET_LINK_LIBRARIES(blist_test gtest_main)
TARGET_LINK_LIBRARIES(blist_test ${LIB_NAME})

ADD_TEST(run_blist_tests blist_test)

ADD_TEST(run_blist_exe blist "${PROJECT_SOURCE_DIR}/${PROJECT_NAME}_version.h")

## Test step disabled 2019-08-22 - Causes SegFault when running on GitHub Actions build servers.
## ADD_TEST(run_filter_exe file_filter "${PROJECT_SOURCE_DIR}/${PROJECT_NAME}_version.h")

# Install

INCLUDE(CMakePackageConfigHelpers)
WRITE_BASIC_PACKAGE_VERSION_FILE("${PROJECT_NAME}ConfigVersion.cmake"
        VERSION ${PROJECT_VERSION}
        COMPATIBILITY SameMajorVersion)

# locations are provided by GNUInstallDirs
INSTALL(TARGETS ${PROJECT_NAME}
        EXPORT ${PROJECT_NAME}_Targets
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        )
