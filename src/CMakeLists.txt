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

INCLUDE(WarningsAsErrors)
INCLUDE(CppcheckTargets)
add_cppcheck(blist UNUSED_FUNCTIONS STYLE POSSIBLE_ERROR FAIL_ON_WARNINGS)
add_cppcheck(file_filter UNUSED_FUNCTIONS STYLE POSSIBLE_ERROR FAIL_ON_WARNINGS)

# Testing

ENABLE_TESTING()

ADD_TEST(NAME run_blist_exe
        COMMAND $<TARGET_FILE:blist> "${CMAKE_CURRENT_SOURCE_DIR}/blist_version.h"
)

ADD_TEST(NAME run_filter_exe
        COMMAND $<TARGET_FILE:file_filter> "${CMAKE_CURRENT_SOURCE_DIR}/blist_version.h"
)

# Install

SET(INSTALL_TARGETS
    blist
    file_filter
    )

install(TARGETS ${INSTALL_TARGETS} DESTINATION bin)
