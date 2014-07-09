#ifndef NVIM_OS_OS_DEFS_H
#define NVIM_OS_OS_DEFS_H

/* Values returned by mch_nodetype() */
#define NODE_NORMAL     0       /* file or directory, check with os_isdir()*/
#define NODE_WRITABLE   1       /* something we can write to (character
                                   device, fifo, socket, ..) */
#define NODE_OTHER      2       /* non-writable thing (e.g., block device) */

#ifdef WIN32
# include "nvim/os/win_defs.h"
#else
# include "nvim/os/unix_defs.h"
#endif

#endif  // NVIM_OS_DEFS_H
