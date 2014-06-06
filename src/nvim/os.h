#ifndef NVIM_OS_H
#define NVIM_OS_H

#ifdef UNIX
#include "nvim/os_unix_defs.h"
#include "nvim/os_unix.h"
#endif

#ifdef WIN32
#include "nvim/os_mingw_defs.h"
#include "nvim/os_mingw.h"
#endif

#endif
