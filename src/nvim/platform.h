#ifndef NVIM_PLATFORM_H
#define NVIM_PLATFORM_H

#ifdef UNIX
#include "nvim/os_unix_defs.h"
#endif

#ifdef WIN32
#include "nvim/os_mingw_defs.h"
#endif

#endif
