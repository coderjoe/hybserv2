/*
 * init.h
 * Copyright (C) 1999 Patrick Alken
 *
 * $Id$
 */

#ifndef INCLUDED_init_h
#define INCLUDED_init_h

struct Luser;

/*
 * Prototypes
 */

void ProcessSignal(int signal);
void InitListenPorts();
void InitLists();
void InitSignals();
void PostCleanup();
void InitServs(struct Luser *servptr);

#endif /* INCLUDED_init_h */