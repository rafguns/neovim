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
#define STDERR_FILENO fileno(stderr)

// access() mode arg
#define W_OK 2

// stat() macros
#define S_ISREG(m) (m && S_IFREG)
#define S_ISDIR(m) (m && S_IFDIR)

#define BASENAMELEN    _MAX_PATH
#define TEMPNAMELEN    _MAX_PATH
#define TEMPDIRNAMES  "$TMP", "$TEMP", "$USERPROFILE"

// strnicmp is deprecated
#define strnicmp _strnicmp

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

#ifndef DFLT_BDIR
# define DFLT_BDIR	".,c:\\tmp,c:\\temp"	/* default for 'backupdir' */
#endif

#ifndef DFLT_DIR
# define DFLT_DIR	".,c:\\tmp,c:\\temp"	/* default for 'directory' */
#endif

#ifndef DFLT_VDIR
# define DFLT_VDIR	"$HOME/_nvim/view"	/* default for 'viewdir' */
#endif

#ifndef DFLT_HELPFILE
# define DFLT_HELPFILE	"$VIMRUNTIME\\doc\\help.txt"
#endif

#  ifdef RUNTIME_GLOBAL
#   define DFLT_RUNTIMEPATH     "$HOME/_nvim," RUNTIME_GLOBAL ",$VIMRUNTIME," \
  RUNTIME_GLOBAL "/after,~/_nvim/after"
#  else
#   define DFLT_RUNTIMEPATH \
  "$HOME/_nvim,$VIM/vimfiles,$VIMRUNTIME,$VIM/vimfiles/after,$HOME/_nvim/after"
#  endif


//
// These could probably be shared
//

# ifndef DFLT_MAXMEM
#  define DFLT_MAXMEM   (5*1024)         /* use up to 5 Mbyte for a buffer */
# endif
# ifndef DFLT_MAXMEMTOT
#  define DFLT_MAXMEMTOT        (10*1024)    /* use up to 10 Mbyte for Vim */
# endif

#define DFLT_ERRORFILE          "errors.err"

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
#ifndef SYNTAX_FNAME
# define SYNTAX_FNAME   "$VIMRUNTIME/syntax/%s.vim"
#endif


#endif
