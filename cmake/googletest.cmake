# Google Test Framework

# https://github.com/google/googletest/blob/master/googletest/README.md

CMAKE_MINIMUM_REQUIRED(VERSION 3.12)

# Prevent overriding the parent project's compiler/linker settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

INCLUDE(FetchContent)

FetchContent_Declare(googletest
        URL https://github.com/google/googletest/archive/release-1.10.0.tar.gz
        URL_HASH SHA256=9dc9157a9a1551ec7a7e43daea9a694a0bb5fb8bec81235d8a1e6ef64c716dcb
        SOURCE_DIR googletest-src
        )

FetchContent_GetProperties(googletest)
if (NOT googletest_POPULATED)
    FetchContent_Populate(googletest)

    # Add googletest directly to our build.
    # This defines the gtest and gtest_main targets.
    add_subdirectory(${googletest_SOURCE_DIR}
            ${googletest_BINARY_DIR}
            EXCLUDE_FROM_ALL)
endif ()

set(googletest_include ${googletest_SOURCE_DIR}/googletest/include/)
