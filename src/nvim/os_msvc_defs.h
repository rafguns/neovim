#ifndef NVIM_OS_WIN_H
#define NVIM_OS_WIN_H

#include <uv.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include <io.h> // open/close
#include <fcntl.h>

typedef uv_uid_t uid_t;

#ifndef MSVC_CLANG
// MSVC 2013 cl does not have these
#define restrict __restrict
#define inline __inline
#endif


#ifndef VIMINFO_FILE
# define VIMINFO_FILE          "$HOME\\_viminfo"
#endif


#endif
