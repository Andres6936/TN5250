CMAKE_MINIMUM_REQUIRED(VERSION 3.14)
PROJECT(Tan CXX)

ADD_LIBRARY(Tan.Protocol
        Source/Protocol/buffer.cpp
        Source/Protocol/conf.cpp
        Source/Protocol/dbuffer.cpp
        Source/Protocol/debug.cpp
        Source/Protocol/display.cpp
        Source/Protocol/field.cpp
        Source/Protocol/macro.cpp
        Source/Protocol/menu.cpp
        Source/Protocol/printsession.cpp
        Source/Protocol/record.cpp
        Source/Protocol/scrollbar.cpp
        Source/Protocol/scs.cpp
        Source/Protocol/session.cpp
        Source/Protocol/sslstream.cpp
        Source/Protocol/stream.cpp
        Source/Protocol/telnetstr.cpp
        Source/Protocol/terminal.cpp
        Source/Protocol/utility.cpp
        Source/Protocol/version.cpp
        Source/Protocol/window.cpp
        Source/Protocol/wtd.cpp
        )
TARGET_COMPILE_DEFINITIONS(Tan.Protocol PRIVATE -DSYSCONFDIR="tmp")
TARGET_INCLUDE_DIRECTORIES(Tan.Protocol PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include/Protocol>)

ADD_EXECUTABLE(Tan.App
        Source/Console/tn5250.cpp
        Source/Console/cursesterm.cpp
        )
TARGET_INCLUDE_DIRECTORIES(Tan.App PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include/Console>)
TARGET_LINK_LIBRARIES(Tan.App PRIVATE Tan.Protocol)


#[[ Set CURSES_NEED_NCURSES to TRUE before the find_package(Curses) call if
 NCurses functionality is required. Set CURSES_NEED_WIDE to TRUE before the
 find_package(Curses) call if unicode functionality is required. ]]
#
SET(CURSES_NEED_NCURSES TRUE)
SET(CURSES_NEED_WIDE TRUE)

FIND_PACKAGE(Curses)

IF (CURSES_FOUND)
    TARGET_COMPILE_DEFINITIONS(Tan.App PRIVATE -DUSE_CURSES)
    TARGET_INCLUDE_DIRECTORIES(Tan.App PRIVATE ${CURSES_INCLUDE_DIRS})
    TARGET_LINK_LIBRARIES(Tan.App PRIVATE ${CURSES_LIBRARIES})

ELSE ()
    MESSAGE(FATAL_ERROR "Not support to NCurses")
ENDIF ()