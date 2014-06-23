#ifndef NVIM_OS_DEFS_H
#define NVIM_OS_DEFS_H

#ifdef UNIX
#include "nvim/platform/os_unix_defs.h"
#endif

#ifdef MSVC
#include "nvim/platform/os_msvc_defs.h"
#endif

#endif
