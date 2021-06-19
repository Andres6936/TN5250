CMAKE_MINIMUM_REQUIRED(VERSION 3.14)
PROJECT(Tan C)

INCLUDE_DIRECTORIES(.)
INCLUDE_DIRECTORIES(lib5250)

ADD_LIBRARY(Tan.Protocol
        lib5250/buffer.c
        lib5250/conf.c
        lib5250/dbuffer.c
        lib5250/debug.c
        lib5250/display.c
        lib5250/field.c
        lib5250/macro.c
        lib5250/menu.c
        lib5250/printsession.c
        lib5250/record.c
        lib5250/scrollbar.c
        lib5250/scs.c
        lib5250/session.c
        lib5250/sslstream.c
        lib5250/stream.c
        lib5250/telnetstr.c
        lib5250/terminal.c
        lib5250/utility.c
        lib5250/version.c
        lib5250/window.c
        lib5250/wtd.c
)
TARGET_COMPILE_DEFINITIONS(Tan.Protocol PRIVATE -DSYSCONFDIR="tmp")
TARGET_INCLUDE_DIRECTORIES(Tan.Protocol PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/lib5250/>)

ADD_EXECUTABLE(Tan.App
        curses/tn5250.c
        curses/cursesterm.c
        )
TARGET_LINK_LIBRARIES(Tan.App PRIVATE Tan.Protocol)


#[[ Set CURSES_NEED_NCURSES to TRUE before the find_package(Curses) call if
 NCurses functionality is required. Set CURSES_NEED_WIDE to TRUE before the
 find_package(Curses) call if unicode functionality is required. ]]#
SET(CURSES_NEED_NCURSES TRUE)
SET(CURSES_NEED_WIDE TRUE)

FIND_PACKAGE(Curses)

IF (CURSES_FOUND)
    TARGET_INCLUDE_DIRECTORIES(Tan.App PRIVATE ${CURSES_INCLUDE_DIRS})
    TARGET_LINK_LIBRARIES(Tan.App PRIVATE ${CURSES_LIBRARIES})

ELSE()
    MESSAGE(FATAL_ERROR "Not support to NCurses")
ENDIF()