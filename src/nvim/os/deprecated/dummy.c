//
// Dummy functions that allow Neovim to compile when
// the implementing a new platform
//

#include <stdbool.h>
#include "nvim/vim.h"
#include "nvim/api/private/handle.h"
#include "nvim/os/time.h"
#include "nvim/os/event.h"
#include "nvim/term.h"

void mch_restore_title(int which)
{
}

int mch_has_wildcard(char_u *p)
{
  return false;
}

void mch_hide(char_u *name)
{
}

int mch_nodetype(char_u *name)
{
  return NODE_OTHER;
}

void mch_early_init()
{
  handle_init();
  time_init();
}

void mch_exit(int r)
{
}

void mch_init()
{
  Columns = 80;
  Rows = 24;

  out_flush();

#ifdef MACOS_CONVERT
  mac_conv_init();
#endif

  event_init();
}

void mch_setmouse(int on)
{
}

int mch_has_exp_wildcard(char_u *p)
{
  return false;
}

void mch_set_shellsize()
{
}

int mch_get_shellsize()
{
  return FAIL;
}

/*
 * Write s[len] to the screen.
 */
void mch_write(char_u *s, int len)
{
  ignored = (int)write(1, (char *)s, len);
  if (p_wd)             /* Unix is too fast, slow down a bit more */
    os_microdelay(p_wd, false);
}

void mch_settitle(char_u *title, char_u *icon)
{
}

void mch_suspend()
{
}

void mch_settmode(int tmode)
{
}

int 
unix_expandpath (
    garray_T *gap,
    char_u *path,
    int wildoff,
    int flags,                      /* EW_* flags */
    int didstar                    /* expanded "**" once already */
)
{
  return 0;
}

int mch_can_restore_title()
{
  return false;
}

int mch_can_restore_icon()
{
  return false;
}

uid_t getuid(void)
{
  return -1;
}

