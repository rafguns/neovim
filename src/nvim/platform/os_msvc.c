
#include "nvim/vim.h"
#include "nvim/path.h"
#include "nvim/screen.h"
#include "nvim/strings.h"
#include "nvim/os/os.h"
#include "nvim/term.h"
#include "nvim/ui.h"
#include "nvim/os/time.h"
#include "nvim/os/event.h"
#include "nvim/os/input.h"
#include "nvim/os/shell.h"
#include "nvim/os/signal.h"
#include "nvim/os/job.h"

#ifdef INCLUDE_GENERATED_DECLARATIONS
# include "platform/os_msvc.c.generated.h"
#endif

/*
 * Set the window title and icon.
 */
void mch_settitle(char_u *title, char_u *icon)
{

}

/*
 * Restore the window/icon title.
 * "which" is one of:
 *  1  only restore title
 *  2  only restore icon
 *  3  restore title and icon
 */
void mch_restore_title(int which)
{
}

/*
 * Check what "name" is:
 * NODE_NORMAL: file or directory (or doesn't exist)
 * NODE_WRITABLE: writable device, socket, fifo, etc.
 * NODE_OTHER: non-writable things
 */
int mch_nodetype(char_u *name)
{
  struct stat st;

  // FIXME: do we still need the checks from Vim?
  if (stat((char *)name, &st))
    return NODE_NORMAL;
  if (S_ISREG(st.st_mode) || S_ISDIR(st.st_mode))
    return NODE_NORMAL;
  /* Everything else is writable? */
  return NODE_WRITABLE;
}

/*
* Return TRUE if "p" contain a wildcard or a "~1" kind of thing (could be a
* shortened file name).
*/
int mch_has_wildcard(char_u *p)
{
	for ( ; *p; mb_ptr_adv(p)) {
		if (vim_strchr((char_u *)"?*$[", *p) != NULL
				|| (*p == '~' && p[1] != NUL)) {
			return TRUE;
		}
	}
	return FALSE;
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

void mch_early_init()
{
}

void mch_exit(int r)
{

}

/*
 * Set hidden flag for "name".
 */
void mch_hide(char_u *name)
{
  /* TODO */
}

int mch_can_restore_title()
{
  return 0;
}

int mch_can_restore_icon()
{
  return 0;
}

/*
 * Set mouse clicks on or off.
 */
void mch_setmouse(int on)
{
}

/*
* Return TRUE if "p" contain a wildcard that can be expanded by
* dos_expandpath().
*/
int mch_has_exp_wildcard(char_u *p)
{
	for ( ; *p; mb_ptr_adv(p))
	{
		if (vim_strchr((char_u *)"?*[", *p) != NULL
				|| (*p == '~' && p[1] != NUL)) {
			return TRUE;
		}
	}
	return FALSE;
}


int  unix_expandpath (
    garray_T *gap,
    char_u *path,
    int wildoff,
    int flags,                      /* EW_* flags */
    int didstar                    /* expanded "**" once already */
)
{
	return 0;
}


void mch_settmode(int tmode)
{
}


void mch_set_shellsize()
{
}

int mch_get_shellsize()
{
	return FAIL;
}

void mch_write(char_u *s, int len)
{
}

void mch_suspend()
{
}



