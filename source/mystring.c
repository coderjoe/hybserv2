/*
 * HybServ TS Services, Copyright (C) 1998-1999 Patrick Alken
 * This program comes with absolutely NO WARRANTY
 *
 * Should you choose to use and/or modify this source code, please
 * do so under the terms of the GNU General Public License under which
 * this program is distributed.
 *
 * $Id$
 */

#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#include "alloc.h"
#include "config.h"
#include "defs.h"
#include "hybdefs.h"
#include "log.h"
#include "match.h"

/*
StrToupper()
  args: char *str
  purpose: convert the string 'str' to uppercase
  return: the uppercase string
*/

char *
StrToupper(char *str)

{
  int ii;
  static char retstr[MAXLINE];

  if (!str)
    return (NULL);

  retstr[0] = '\0';
  for (ii = 0; ii < strlen(str); ++ii)
    retstr[ii] = ToUpper(str[ii]);

  retstr[ii] = '\0';

  return (retstr);
} /* StrToupper() */

/*
StrTolower()
  args: char *str
  purpose: convert the string 'str' to lowercase
  return: the lowercase string
*/

char *
StrTolower(char *str)

{
  int ii;
  static char retstr[MAXLINE];

  if (!str)
    return ((char *) NULL);

  retstr[0] = '\0';
  for (ii = 0; ii < strlen(str); ++ii)
    retstr[ii] = ToLower(str[ii]);

  retstr[ii] = '\0';

  return (retstr);
} /* StrTolower() */

/*
GetString()
 Reverse the array av back into a normal string assuming there
are 'ac' indices in the array. Space is allocated for the new
string.
*/

char *
GetString(int ac, char **av)

{
  char *final;
  char temp[MAXLINE];
  int ii;

  final = (char *) MyMalloc(sizeof(char));
  *final = '\0';

  ii = 0;
  while (ii < ac)
  {
    if ((ii + 1) >= ac)
    {
      /*
       * This is the last arguement, so don't put an extra
       * space on the end
       */
      sprintf(temp, "%s",  av[ii]);
    }
    else
      sprintf(temp, "%s ", av[ii]);

    final = (char *) MyRealloc(final,
                      strlen(final) + strlen(temp) + sizeof(char));
    strcat(final, temp);

    ++ii;
  }

  return (final);
} /* GetString() */

/*
SplitBuf()
 Take string "buff" and insert NULLs in the spaces between words.
Keep pointers to the beginning of each word, and store them
in "array".
 Returns the number of words in "buff"
*/

int
SplitBuf(char *buff, char ***array)

{
  int argsize = 8;
  int acnt,
      ii;
  char *temp1, *tempbuf;

  tempbuf = buff;

  ii = strlen(tempbuf);

  /* try to kill trailing \r or \n chars */
  if (IsEOL(tempbuf[ii - 1]))
    tempbuf[ii - 1] = '\0';

  /*
   * When hybrid sends channel bans during a netjoin, it leaves
   * a preceding space (not sure why) - just make sure there
   * are no preceding spaces
   */
  while (IsSpace(*tempbuf))
    ++tempbuf;

  *array = (char **) MyMalloc(sizeof(char *) * argsize);
  acnt = 0;
  while (*tempbuf)
  {
    if (acnt == argsize)
    {
      argsize += 8;
      *array = (char **) MyRealloc(*array, sizeof(char *) * argsize);
    }

    if ((*tempbuf == ':') && (acnt != 0))
    {
      (*array)[acnt++] = tempbuf;
      /* (*array)[acnt++] = tempbuf + 1; */
      tempbuf = "";
    }
    else
    {
      temp1 = strpbrk(tempbuf, " ");
      if (temp1)
      {
        *temp1++ = 0;
        while (IsSpace(*temp1))
          ++temp1;
      }
      else
        temp1 = tempbuf + strlen(tempbuf);

      (*array)[acnt++] = tempbuf;
      tempbuf = temp1;
    }
  }

  return (acnt);
} /* SplitBuf() */