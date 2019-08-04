cmake_minimum_required(VERSION 3.12)
project(blist)

set(CMAKE_CXX_STANDARD 14)

SET(lib_SRCS
        libsrc/File.cc
        libsrc/FileName.cc
        libsrc/fileutil.cc
        libsrc/proginfo.cc
        libsrc/TextBox.cc
        libsrc/utildbug.cc
        libsrc/utilmsg.cc
        )
SET(lib_HDRS
        libsrc/File.h
        libsrc/FileName.h
        libsrc/fileutil.h
        libsrc/proginfo.h
        libsrc/TextBox.h
        libsrc/utildbug.h
        libsrc/utilmsg.h
        )

SET(blist_SRCS main.cc blist.cc blist.h)

ADD_LIBRARY(mylib STATIC ${lib_HDRS} ${lib_SRCS})
add_executable(blist ${blist_SRCS} ${lib_HDRS} ${lib_SRCS})

install(TARGETS blist RUNTIME DESTINATION bin)
