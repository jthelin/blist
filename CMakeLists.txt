CMAKE_MINIMUM_REQUIRED(VERSION 3.12)

PROJECT(blist
    VERSION 2.1.3
    DESCRIPTION "Bulk list contents of text file(s) to stdout (for redirection), preceded by header block with file info"
    HOMEPAGE_URL "https://github.com/jthelin/blist"
    LANGUAGES CXX
    )
SET(PROJECT_AUTHOR "J.Thelin")
SET(PROJECT_STATUS "")

SET(CMAKE_CXX_STANDARD 17)

INCLUDE(GNUInstallDirs)

STRING(TIMESTAMP BUILD_DATE "%Y-%m-%d")
STRING(TIMESTAMP BUILD_TIMESTAMP "%Y-%m-%d_%H:%M:%S")

MESSAGE(STATUS "-- Build ${PROJECT_NAME} with build config = ${CMAKE_BUILD_TYPE}")

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

# Google Test Framework
INCLUDE(googletest)

# Cmake Modules - For add_cppcheck
INCLUDE(cmake-modules)

# Enable Address Sanitizer in Debug builds
IF(NOT (MSVC))
    string(APPEND CMAKE_CXX_FLAGS_DEBUG " -fsanitize=address")
    string(APPEND CMAKE_LINKER_FLAGS_DEBUG " -fsanitize=address")
ENDIF()

# Burn version info into app header file.
CONFIGURE_FILE(
    ${CMAKE_CURRENT_SOURCE_DIR}/tmpl_version.h.in
    ${PROJECT_SOURCE_DIR}/src/${PROJECT_NAME}_version.h)

ADD_SUBDIRECTORY(libsrc)
ADD_SUBDIRECTORY(src)

# Testing
ENABLE_TESTING()
ADD_SUBDIRECTORY(tests)

# Install

INCLUDE(CMakePackageConfigHelpers)
WRITE_BASIC_PACKAGE_VERSION_FILE("${PROJECT_NAME}ConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion)

# locations are provided by GNUInstallDirs
INSTALL(TARGETS ${INSTALL_TARGETS}
    EXPORT ${PROJECT_NAME}_Targets
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    )
