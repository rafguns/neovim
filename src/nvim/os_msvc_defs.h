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

#define STDOUT_FILENO fileno(stdout)

#ifndef MSVC_CLANG
// MSVC 2013 cl does not have these
#define restrict __restrict
#define inline __inline
#define __func__ __FUNCTION__
#endif

#define BASENAMELEN    _MAX_PATH
#define TEMPNAMELEN    _MAX_PATH
#define TEMPDIRNAMES  "$TMP", "$TEMP", "$USERPROFILE"

//
// System dependent paths
//
//
#ifndef VIMINFO_FILE
# define VIMINFO_FILE	"$HOME\\_viminfo"
#endif

#ifndef VIMRC_FILE
# define VIMRC_FILE     "_nvimrc"
#endif

#ifndef EXRC_FILE
# define EXRC_FILE 	"_exrc"
#endif

#ifndef EVIM_FILE
# define EVIM_FILE      "$VIMRUNTIME\\evim.vim"
#endif

#ifndef USR_VIMRC_FILE
# define USR_VIMRC_FILE	"$HOME\\_nvimrc"
#endif

#ifndef USR_EXRC_FILE
# define USR_EXRC_FILE	"$HOME\\_exrc"
#endif

//
// These could probably be shared
//

#ifndef INDENT_FILE
# define INDENT_FILE    "indent.vim"
#endif
#ifndef FILETYPE_FILE
# define FILETYPE_FILE  "filetype.vim"
#endif
#ifndef FTPLUGIN_FILE
# define FTPLUGIN_FILE  "ftplugin.vim"
#endif
#ifndef FTPLUGOF_FILE
# define FTPLUGOF_FILE  "ftplugof.vim"
#endif
#ifndef FTOFF_FILE
# define FTOFF_FILE     "ftoff.vim"
#endif
#ifndef INDOFF_FILE
# define INDOFF_FILE    "indoff.vim"
#endif


#endif
