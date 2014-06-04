#ifndef NVIM_OS_H
#define NVIM_OS_H

#ifdef UNIX
#include "nvim/os_unix.h"
#endif

// FIXME
#ifdef WIN32
#include "nvim/os_mingw.h"
#endif

#endif
