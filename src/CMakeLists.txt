# Applications

SET(LIB_NAME ${PROJECT_NAME}_lib)

ADD_EXECUTABLE(blist
    blist.cc
    blist.h
    blist_version.h
    ${lib_HDRS})
TARGET_INCLUDE_DIRECTORIES(blist PRIVATE ../libsrc)
TARGET_LINK_LIBRARIES(blist ${LIB_NAME})

ADD_EXECUTABLE(file_filter
    file_filter.cc
    ${lib_HDRS})
TARGET_INCLUDE_DIRECTORIES(file_filter PRIVATE ../libsrc)
TARGET_LINK_LIBRARIES(file_filter ${LIB_NAME})

INCLUDE(CppcheckTargets)
add_cppcheck(blist UNUSED_FUNCTIONS STYLE POSSIBLE_ERROR FAIL_ON_WARNINGS)
add_cppcheck(file_filter UNUSED_FUNCTIONS STYLE POSSIBLE_ERROR FAIL_ON_WARNINGS)

# Testing

ENABLE_TESTING()

ADD_TEST(run_blist_exe blist "${CMAKE_CURRENT_SOURCE_DIR}/blist_version.h")

ADD_TEST(run_filter_exe file_filter "${CMAKE_CURRENT_SOURCE_DIR}/blist_version.h")

# Install

SET(INSTALL_TARGETS ${PROJECT_NAME}
    blist
    file_filter
    )
