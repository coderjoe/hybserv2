/*
 * mystring.h
 * Copyright (C) 1999 Patrick Alken
 *
 * $Id$
 */

#ifndef INCLUDED_mystring_h
#define INCLUDED_mystring_h

int Snprintf(char *dest, size_t size, char *format, ...);
char *StrToupper(char *str);
char *StrTolower(char *str);
char *GetString(int ac, char **av);
int SplitBuf(char *buf, char ***array);

#endif /* INCLUDED_mystring_h */