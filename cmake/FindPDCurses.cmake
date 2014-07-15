# - Try to find PDCurses
# Once done, this will define
#
#  PDCurses_FOUND        - system has PDCurses
#  PDCurses_INCLUDE_DIRS - the PDCurses include directories
#  PDCurses_LIBRARIES    - link these to use PDCurses

include(CheckCSourceCompiles)
include(LibFindMacros)

find_path(PDCurses_INCLUDE_DIR
    NAMES curses.h term.h
)

find_library(PDCurses_LIBRARY
    NAMES pdcurses libpdcurses.a curses
)

if (PDCurses_INCLUDE_DIR)
  set(CMAKE_REQUIRED_INCLUDES "${PDCurses_INCLUDE_DIR}")
endif()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(PDCurses DEFAULT_MSG
		PDCurses_LIBRARY PDCurses_INCLUDE_DIR)


