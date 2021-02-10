project(ApprovalTests-download NONE)

include(ExternalProject)
ExternalProject_Add(ApprovalTests
    GIT_REPOSITORY https://github.com/approvals/ApprovalTests.cpp.git
    GIT_TAG v.10.7.1
    SOURCE_DIR "${CMAKE_CURRENT_BINARY_DIR}/ApprovalTests-src"
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
    TEST_COMMAND ""
    )

set(ApprovalTests_include
    ${CMAKE_CURRENT_BINARY_DIR}/ApprovalTests-src/
    ${CMAKE_CURRENT_BINARY_DIR}/ApprovalTests-src/ApprovalTests
    )
