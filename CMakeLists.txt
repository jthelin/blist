CMAKE_MINIMUM_REQUIRED(VERSION 3.12)
SET(CMAKE_CXX_STANDARD 14)

PROJECT(blist)

# Application

FILE(GLOB lib_SRCS CONFIGURE_DEPENDS "libsrc/*.cc")
FILE(GLOB lib_HDRS CONFIGURE_DEPENDS "libsrc/*.h")

SET(blist_SRCS main.cc blist.cc blist.h)

ADD_LIBRARY(mylib STATIC ${lib_HDRS} ${lib_SRCS})
ADD_EXECUTABLE(blist ${blist_SRCS} ${lib_HDRS} ${lib_SRCS})

# Google Test Framework

# https://github.com/google/googletest/blob/master/googletest/README.md

# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
    RESULT_VARIABLE result
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
    message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
    RESULT_VARIABLE result
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
    message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker settings on Windows
SET(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build.
# This defines the gtest and gtest_main targets.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
        ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
        EXCLUDE_FROM_ALL)

# Testing

ENABLE_TESTING()

FILE(GLOB test_SRCS CONFIGURE_DEPENDS "tests/*.cc")

# Now simply link against gtest or gtest_main as needed.
ADD_EXECUTABLE(blist_test ${test_SRCS} ${lib_HDRS} ${lib_SRCS})
TARGET_LINK_LIBRARIES(blist_test gtest_main)

ADD_TEST(run_blist_tests blist_test)

ADD_TEST(run_blist_exe blist ${CMAKE_SOURCE_DIR}/blist.h)

# Install

INSTALL(TARGETS blist RUNTIME DESTINATION bin)
