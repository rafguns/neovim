#ifndef NVIM_OS_WIN_H
#define NVIM_OS_WIN_H

//
// Tested on win32 MSVC 2013 using clang
//
//

#include <uv.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include <io.h> // open/close
#include <fcntl.h>

typedef uv_uid_t uid_t;


#ifndef VIMINFO_FILE
# define VIMINFO_FILE          "$HOME\\_viminfo"
#endif


#endif
