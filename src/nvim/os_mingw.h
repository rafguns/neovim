#ifndef NEOVIM_OS_MINGW_H
#define NEOVIM_OS_MINGW_H

#include "nvim/os/shell.h"

void mch_settitle(char_u *title, char_u *icon);
int mch_has_wildcard(char_u *p);
void mch_restore_title(int which);
int mch_nodetype(char_u *name);
void mch_hide(char_u *name);
int mch_can_restore_title(void);
int mch_can_restore_icon(void);
void mch_setmouse(int on);
int mch_has_exp_wildcard(char_u *p);
void mch_exit(int r);
void mch_init(void);
void mch_early_init(void);
void mch_settmode(int tmode);
void mch_suspend();
void mch_write(char_u *s, int len);
int mch_get_shellsize();
void mch_set_shellsize();

#endif
