# Testing

ENABLE_TESTING()

SET(TEST_EXE ${PROJECT_NAME}_test)
SET(LIB_NAME ${PROJECT_NAME}_lib)

FILE(GLOB test_SRCS CONFIGURE_DEPENDS "*.cc")

# Now simply link against gtest or gtest_main as needed.
ADD_EXECUTABLE(${TEST_EXE}
    ${test_SRCS}
    ${lib_HDRS}
    )
TARGET_INCLUDE_DIRECTORIES(${TEST_EXE} PRIVATE
    ${googletest_include}
    )
TARGET_LINK_LIBRARIES(${TEST_EXE}
    gtest_main
    ${LIB_NAME}
    )

ADD_TEST(NAME run_blist_tests
        COMMAND $<TARGET_FILE:${TEST_EXE}>
)
