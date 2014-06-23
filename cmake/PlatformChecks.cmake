include (CheckFunctionExists) 
include (CheckIncludeFiles)
include (CheckSymbolExists)

# Some of these variables are not used by Neovim anymore
# even if they are in config.h.in (e.g. setenv)
# For those cases I just raise an error since it means
# Neovim implicitly assumes thoses functions/headers exist

# Headers

check_include_files(dirent.h HAVE_DIRENT_H)
check_include_files(dlfcn.h HAVE_DLFCN_H)
check_include_files(fcntl.h HAVE_FCNTL_H)
check_include_files(iconv.h HAVE_ICONV_H)
check_include_files(langinfo.h HAVE_LANGINFO_H)
check_include_files(libgen.h HAVE_LIBGEN_H)
check_include_files(locale.h HAVE_LOCALE_H)
check_include_files(pwd.h HAVE_PWD_H)
check_include_files(strings.h HAVE_STRINGS_H)
check_include_files(stropts.h HAVE_STROPTS_H)
check_include_files(sys/ioctl.h HAVE_SYS_IOCTL_H)
check_include_files(sys/param.h HAVE_SYS_PARAM_H)
# FIXME: check vim.h, I think we can get rid of this
check_include_files(sys/select.h HAVE_SYS_SELECT_H)
check_include_files(sys/time.h HAVE_SYS_TIME_H)
check_include_files(sys/wait.h HAVE_SYS_WAIT_H)
if (NOT HAVE_SYS_WAIT_H AND UNIX)
	# See if_cscope.c
	message(SEND_ERROR "header sys/wait.h is required for UNIX")
endif()
check_include_files(sys/utsname.h HAVE_SYS_UTSNAME_H)
check_include_files(utime.h HAVE_UTIME_H)
check_include_files(termcap.h HAVE_TERMCAP_H)
check_include_files(termios.h HAVE_TERMIOS_H)
check_include_files(termio.h HAVE_TERMIO_H)
check_include_files(unistd.h HAVE_UNISTD_H)
check_include_files(utime.h HAVE_UTIME_H)

# Functions

check_function_exists(fchown HAVE_FCHOWN)
check_function_exists(fseeko HAVE_FSEEKO)
check_function_exists(fsync HAVE_FSYNC)
check_function_exists(getpwent HAVE_GETPWENT)
check_function_exists(getpwnam HAVE_GETPWNAM)
check_function_exists(getpwuid HAVE_GETPWUID)
check_function_exists(gettimeofday HAVE_GETTIMEOFDAY)
check_function_exists(iconv HAVE_ICONV)
check_function_exists(lstat HAVE_LSTAT)
if (UNIX AND NOT HAVE_LSTAT)
	# os_unix.c uses lstat.c
	message(SEND_ERROR "lstat() function not found on your system.")
endif()
check_function_exists(mkdtemp HAVE_MKDTEMP)
check_function_exists(mkdtemp HAVE_PUTENV)
check_function_exists(opendir HAVE_OPENDIR)
check_function_exists(readlink HAVE_READLINK)
check_function_exists(setenv HAVE_SETENV)
if (UNIX AND NOT HAVE_SETENV)
	message(SEND_ERROR "setenv() function not found on your system.")
endif()
check_function_exists(setpgid HAVE_SETPGID)
check_function_exists(setsid HAVE_SETSID)
check_function_exists(sigaction HAVE_SIGACTION)
check_function_exists(sigvec HAVE_SIGVEC)
check_function_exists(strcasecmp HAVE_STRCASECMP)
check_function_exists(strncasecmp HAVE_STRNCASECMP)
check_function_exists(utime HAVE_UTIME)
check_function_exists(utimes HAVE_UTIMES)

# Symbols

check_symbol_exists(FD_CLOEXEC "fcntl.h" HAVE_FD_CLOEXEC)

