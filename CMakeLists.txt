CMAKE_MINIMUM_REQUIRED(VERSION 3.14)
PROJECT(Tan CXX)

INCLUDE_DIRECTORIES(.)
INCLUDE_DIRECTORIES(lib5250)

ADD_LIBRARY(Tan.Protocol
        lib5250/buffer.cpp
        lib5250/conf.cpp
        lib5250/dbuffer.cpp
        lib5250/debug.cpp
        lib5250/display.cpp
        lib5250/field.cpp
        lib5250/macro.cpp
        lib5250/menu.cpp
        lib5250/printsession.cpp
        lib5250/record.cpp
        lib5250/scrollbar.cpp
        lib5250/scs.cpp
        lib5250/session.cpp
        lib5250/sslstream.cpp
        lib5250/stream.cpp
        lib5250/telnetstr.cpp
        lib5250/terminal.cpp
        lib5250/utility.cpp
        lib5250/version.cpp
        lib5250/window.cpp
        lib5250/wtd.cpp
        )
TARGET_COMPILE_DEFINITIONS(Tan.Protocol PRIVATE -DSYSCONFDIR="tmp")
TARGET_INCLUDE_DIRECTORIES(Tan.Protocol PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/lib5250/>)

ADD_EXECUTABLE(Tan.App
        curses/tn5250.cpp
        curses/cursesterm.cpp
        )
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