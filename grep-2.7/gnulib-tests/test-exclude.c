/* -*- buffer-read-only: t -*- vi: set ro: */
/* DO NOT EDIT! GENERATED AUTOMATICALLY! */
/* Test suite for exclude.
   Copyright (C) 2009, 2010 Free Software Foundation, Inc.
   This file is part of the GNUlib Library.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

#include <config.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>
#include <fnmatch.h>

#include "exclude.h"
#include "progname.h"
#include "error.h"
#include "argmatch.h"

#ifndef FNM_CASEFOLD
# define FNM_CASEFOLD 0
#endif
#ifndef FNM_LEADING_DIR
# define FNM_LEADING_DIR 0
#endif

char const * const exclude_keywords[] = {
  "noescape",
  "pathname",
  "period",
  "leading_dir",
  "casefold",
  "anchored",
  "include",
  "wildcards",
  NULL
};

int exclude_flags[] = {
  FNM_NOESCAPE,
  FNM_PATHNAME,
  FNM_PERIOD,
  FNM_LEADING_DIR,
  FNM_CASEFOLD,
  EXCLUDE_ANCHORED,
  EXCLUDE_INCLUDE,
  EXCLUDE_WILDCARDS
};

ARGMATCH_VERIFY (exclude_keywords, exclude_flags);

/* Some packages define ARGMATCH_DIE and ARGMATCH_DIE_DECL in <config.h>, and
   thus must link with a definition of that function.  Provide it here.  */
#ifdef ARGMATCH_DIE_DECL
#ifndef __attribute__
# if __GNUC__ < 2 || (__GNUC__ == 2 && __GNUC_MINOR__ < 8)
#  define __attribute__(x) /* empty */
# endif
#endif

#ifndef ATTRIBUTE_NORETURN
# define ATTRIBUTE_NORETURN __attribute__ ((__noreturn__))
#endif

ARGMATCH_DIE_DECL ATTRIBUTE_NORETURN;
ARGMATCH_DIE_DECL { exit (1); }
#endif

int
main (int argc, char **argv)
{
  int exclude_options = 0;
  struct exclude *exclude = new_exclude ();

  set_program_name (argv[0]);

  if (argc == 1)
    error (1, 0, "usage: %s file -- words...", argv[0]);

  while (--argc)
    {
      char *opt = *++argv;
      if (opt[0] == '-')
        {
          int neg = 0;
          int flag;
          char *s = opt + 1;

          if (opt[1] == '-' && opt[2] == 0)
            {
              argc--;
              break;
            }
          if (strlen (s) > 3 && memcmp (s, "no-", 3) == 0)
            {
              neg = 1;
              s += 3;
            }
          flag = XARGMATCH (opt, s, exclude_keywords, exclude_flags);
          if (neg)
            exclude_options &= ~flag;
          else
            exclude_options |= flag;
        }
      else if (add_exclude_file (add_exclude, exclude, opt,
                                 exclude_options, '\n') != 0)
        error (1, errno, "error loading %s", opt);
    }

  for (; argc; --argc)
    {
      char *word = *++argv;

      printf ("%s: %d\n", word, excluded_file_name (exclude, word));
    }
  return 0;
}
