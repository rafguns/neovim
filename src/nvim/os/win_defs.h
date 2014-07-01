#ifndef NEOVIM_OS_WIN_DEFS_H
#define NEOVIM_OS_WIN_DEFS_H

#include <windows.h>
#include <uv.h>

#define TEMP_DIR_NAMES {"$TMP", "$TEMP", "$USERPROFILE", ""}
#define TEMP_FILE_PATH_MAXLEN _MAX_PATH

typedef uv_uid_t uid_t;

#endif  // NEOVIM_OS_WIN_DEFS_H
