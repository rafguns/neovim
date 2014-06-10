#include "nvim/vim.h"

#include "nvim/api/private/handle.h"
#include "nvim/vim.h"
#include "nvim/buffer.h"
#include "nvim/charset.h"
#include "nvim/eval.h"
#include "nvim/ex_cmds.h"
#include "nvim/fileio.h"
#include "nvim/getchar.h"
#include "nvim/main.h"
#include "nvim/mbyte.h"
#include "nvim/memline.h"
#include "nvim/memory.h"
#include "nvim/message.h"
#include "nvim/misc1.h"
#include "nvim/misc2.h"
#include "nvim/garray.h"
#include "nvim/path.h"
#include "nvim/screen.h"
#include "nvim/strings.h"
#include "nvim/syntax.h"
#include "nvim/term.h"
#include "nvim/ui.h"
#include "nvim/os/os.h"
#include "nvim/os/time.h"
#include "nvim/os/event.h"
#include "nvim/os/input.h"
#include "nvim/os/shell.h"
#include "nvim/os/job.h"

static char_u *oldtitle = NULL;
static int did_set_title = FALSE;
static char_u *oldicon = NULL;
static int did_set_icon = FALSE;

void mch_settitle(char_u *title, char_u *icon)
{
}

void mch_restore_title(int which)
{
	
}

/*
* Output a newline when exiting.
* Make sure the newline goes to the same stream as the text.
*/
static void exit_scroll()
{
  if (silent_mode)
    return;
  if (newline_on_exit || msg_didout) {
    if (msg_use_printf()) {
      if (info_message)
        mch_msg("\n");
      else
        mch_errmsg("\r\n");
    } else
      out_char('\n');
  } else {
    restore_cterm_colors(); /* get original colors back */
    msg_clr_eos_force(); /* clear the rest of the display */
    windgoto((int)Rows - 1, 0); /* may have moved the cursor */
  }
}

void mch_exit(int r)
{
  exiting = TRUE;

  event_teardown();

  {
    settmode(TMODE_COOK);
    mch_restore_title(3); /* restore xterm title and icon name */
    /*
* When t_ti is not empty but it doesn't cause swapping terminal
* pages, need to output a newline when msg_didout is set. But when
* t_ti does swap pages it should not go to the shell page. Do this
* before stoptermcap().
*/
    if (swapping_screen() && !newline_on_exit)
      exit_scroll();

    /* Stop termcap: May need to check for T_CRV response, which
* requires RAW mode. */
    stoptermcap();

    /*
* A newline is only required after a message in the alternate screen.
* This is set to TRUE by wait_return().
*/
    if (!swapping_screen() || newline_on_exit)
      exit_scroll();

    /* Cursor may have been switched off without calling starttermcap()
* when doing "vim -u vimrc" and vimrc contains ":q". */
    if (full_screen)
      cursor_on();
  }
  out_flush();
  ml_close_all(TRUE); /* remove all memfiles */

#ifdef MACOS_CONVERT
  mac_conv_cleanup();
#endif

#ifdef EXITFREE
  free_all_mem();
#endif

  exit(r);
}

int mch_has_wildcard(char_u *p)
{
  return 0;
}

void mch_settmode(int tmode)
{

}

void mch_early_init()
{
  handle_init();
  time_init();
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

  if (stat((char *)name, &st))
    return NODE_NORMAL;
  if (S_ISREG(st.st_mode) || S_ISDIR(st.st_mode))
    return NODE_NORMAL;
  if (S_ISBLK(st.st_mode)) /* block device isn't writable */
    return NODE_OTHER;
  /* Everything else is writable? */
  return NODE_WRITABLE;
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

int mch_can_restore_title(void)
{
  return FALSE;
}

int mch_can_restore_icon(void)
{
  return FALSE;
}

void mch_setmouse(int on)
{

}

void mch_hide(char_u *name)
{
  /* can't hide a file */
}

/*
* Return TRUE if the string "p" contains a wildcard that mch_expandpath() can
* expand.
*/
int mch_has_exp_wildcard(char_u *p)
{
  for (; *p; mb_ptr_adv(p)) {
    if (*p == '\\' && p[1] != NUL)
      ++p;
    else if (vim_strchr((char_u *)
                 "*?[{'"
                 , *p) != NULL)
      return TRUE;
  }
  return FALSE;
}

/*
* Write s[len] to the screen.
*/
void mch_write(char_u *s, int len)
{
  ignored = (int)write(1, (char *)s, len);
  if (p_wd) /* Unix is too fast, slow down a bit more */
    os_microdelay(p_wd, false);
}

void mch_suspend()
{
}

/*
* Try to get the current window size:
* 1. with an ioctl(), most accurate method
* 2. from the environment variables LINES and COLUMNS
* 3. from the termcap
* 4. keep using the old values
* Return OK when size could be determined, FAIL otherwise.
*/
int mch_get_shellsize()
{
  long rows = 0;
  long columns = 0;
  char_u *p;

  /*
* 1. try using an ioctl. It is the most accurate method.
*
* Try using TIOCGWINSZ first, some systems that have it also define
* TIOCGSIZE but don't have a struct ttysize.
*/
# ifdef TIOCGWINSZ
  {
    struct winsize ws;
    int fd = 1;

    /* When stdout is not a tty, use stdin for the ioctl(). */
    if (!isatty(fd) && isatty(read_cmd_fd))
      fd = read_cmd_fd;
    if (ioctl(fd, TIOCGWINSZ, &ws) == 0) {
      columns = ws.ws_col;
      rows = ws.ws_row;
    }
  }
# else /* TIOCGWINSZ */
# ifdef TIOCGSIZE
  {
    struct ttysize ts;
    int fd = 1;

    /* When stdout is not a tty, use stdin for the ioctl(). */
    if (!isatty(fd) && isatty(read_cmd_fd))
      fd = read_cmd_fd;
    if (ioctl(fd, TIOCGSIZE, &ts) == 0) {
      columns = ts.ts_cols;
      rows = ts.ts_lines;
    }
  }
# endif /* TIOCGSIZE */
# endif /* TIOCGWINSZ */

  /*
* 2. get size from environment
* When being POSIX compliant ('|' flag in 'cpoptions') this overrules
* the ioctl() values!
*/
  if (columns == 0 || rows == 0 || vim_strchr(p_cpo, CPO_TSIZE) != NULL) {
    if ((p = (char_u *)os_getenv("LINES")))
      rows = atoi((char *)p);
    if ((p = (char_u *)os_getenv("COLUMNS")))
      columns = atoi((char *)p);
  }

#ifdef HAVE_TGETENT
  /*
* 3. try reading "co" and "li" entries from termcap
*/
  if (columns == 0 || rows == 0)
    getlinecol(&columns, &rows);
#endif

  /*
* 4. If everything fails, use the old values
*/
  if (columns <= 0 || rows <= 0)
    return FAIL;

  Rows = rows;
  Columns = columns;
  limit_screen_size();
  return OK;
}

/*
* Try to set the window size to Rows and Columns.
*/
void mch_set_shellsize()
{
  if (*T_CWS) {
    /*
* NOTE: if you get an error here that term_set_winsize() is
* undefined, check the output of configure. It could probably not
* find a ncurses, termcap or termlib library.
*/
    term_set_winsize((int)Rows, (int)Columns);
    out_flush();
    screen_start(); /* don't know where cursor is now */
  }
}

