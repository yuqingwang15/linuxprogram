/* Portability cruft.  Include after config.h and sys/types.h.
   Copyright 1996, 1998-2000, 2007, 2009-2010 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street - Fifth Floor, Boston, MA
   02110-1301, USA.  */

#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

#include "binary-io.h"
#include "configmake.h"
#include "dirname.h"
#include "minmax.h"

#if O_BINARY
# define HAVE_DOS_FILE_CONTENTS 1
#endif

#ifdef EISDIR
# define is_EISDIR(e, f) ((e) == EISDIR)
#else
# define is_EISDIR(e, f) 0
#endif

#include <stdlib.h>
#include <stddef.h>
#include <limits.h>
#include <string.h>
#include <ctype.h>

enum { EXIT_TROUBLE = 2 };

#include <gettext.h>
#define N_(String) gettext_noop(String)
#define _(String) gettext(String)

#include <locale.h>

#ifndef initialize_main
#define initialize_main(argcp, argvp)
#endif

#include "unlocked-io.h"
