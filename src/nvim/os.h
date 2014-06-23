#ifndef NVIM_OS_H
#define NVIM_OS_H

#ifdef UNIX
#include "nvim/platform/os_unix.h"
#endif

#ifdef MSVC
#include "nvim/platform/os_msvc.h"
#endif

#endif
