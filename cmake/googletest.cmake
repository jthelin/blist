# Google Test Framework

# https://github.com/google/googletest/blob/master/googletest/README.md

CMAKE_MINIMUM_REQUIRED(VERSION 3.12)

# Prevent overriding the parent project's compiler/linker settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

INCLUDE(FetchContent)

FetchContent_Declare(googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.tar.gz
        URL_HASH SHA256=8ad598c73ad796e0d8280b082cebd82a630d73e73cd3c70057938a6501bba5d7
        SOURCE_DIR googletest-src
        DOWNLOAD_EXTRACT_TIMESTAMP True
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
