#ifndef NVIM_OS_MINGW_H
#define NVIM_OS_MINGW_H



#include <uv.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <sys/time.h>

typedef uv_uid_t uid_t;

// defs

#ifndef VIMINFO_FILE
#  define VIMINFO_FILE "$HOME/_nviminfo"
#endif

#endif
