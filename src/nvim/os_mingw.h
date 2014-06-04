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

#ifndef VIMRC_FILE
# define VIMRC_FILE     "_nvimrc"
#endif

#ifndef EXRC_FILE
# define EXRC_FILE      "_exrc"
#endif

#ifndef USR_EXRC_FILE
#  define USR_EXRC_FILE "$HOME/_exrc"
#endif

#endif
