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

#ifndef FILETYPE_FILE
# define FILETYPE_FILE  "filetype.vim"
#endif
#ifndef FTPLUGIN_FILE
# define FTPLUGIN_FILE  "ftplugin.vim"
#endif
#ifndef INDENT_FILE
# define INDENT_FILE    "indent.vim"
#endif
#ifndef FTOFF_FILE
# define FTOFF_FILE     "ftoff.vim"
#endif
#ifndef FTPLUGOF_FILE
# define FTPLUGOF_FILE  "ftplugof.vim"
#endif
#ifndef INDOFF_FILE
# define INDOFF_FILE    "indoff.vim"
#endif

#ifndef USR_EXRC_FILE
#  define USR_EXRC_FILE "$HOME/_exrc"
#endif


/*
 * MAX_PATH for windows should be around 260 chars
 * libuv sets MAX_PIPENAME as 256, and so do we
 */
#define BASENAMELEN    256
#define TEMPNAMELEN    256

#endif
