/*
 * channel.h
 * Copyright (C) 1999 Patrick Alken
 *
 * $Id$
 */

#ifndef INCLUDED_channel_h
#define INCLUDED_channel_h

#ifndef INCLUDED_sys_time_h
#include <sys/time.h>        /* time_t */
#define INCLUDED_sys_time_h
#endif

#ifndef INCLUDED_hybdefs_h
#include "hybdefs.h"         /* CHANNELLEN ... */
#define INCLUDED_hybdefs_h
#endif

struct Luser;
struct UserChannel;

/*
 * Channel flags
 */
#define CH_VOICED       0x000001 /* user is voiced */
#define CH_OPPED        0x000002 /* user is opped */
#define MODE_O          0x000004 /* someone was +o'd */
#define MODE_V          0x000008 /* someone was +v'd */
#define MODE_L          0x000010 /* channel is +l */
#define MODE_K          0x000020 /* channel is +k */
#define MODE_S          0x000040 /* channel is +s */
#define MODE_P          0x000080 /* channel is +p */
#define MODE_N          0x000100 /* channel is +n */
#define MODE_T          0x000200 /* channel is +t */
#define MODE_M          0x000400 /* channel is +m */
#define MODE_I          0x000800 /* channel is +i */

struct ChannelGecosBan
{
  struct ChannelGecosBan *next, *prev;
  char *who;     /* who set the ban */
  time_t when;   /* when the ban was made */
  char *mask;    /* hostmask of the ban */
};

struct ChannelBan
{
  struct ChannelBan *next, *prev;
  char *who;     /* who set the ban */
  time_t when;   /* when the ban was made */
  char *mask;    /* hostmask of the ban */
};

struct Exception
{
  struct Exception *next, *prev;
  char *who;    /* who set the exception */
  time_t when;  /* when it was set */
  char *mask;   /* exception hostmask */
};

struct ChannelUser
{
  struct ChannelUser *next;
  struct Luser *lptr;   /* pointer to user structure */
  int flags;            /* flags such as opped/voiced */
};

/* Stores info for network channels */
struct Channel

{
  struct Channel *next, *prev, *hnext;

#ifdef BLOCK_ALLOCATION

  char name[CHANNELLEN + 1]; /* channel name */
  char key[KEYLEN + 1];

#else

  char *name;             /* channel name */
  char *key;              /* NULL if no key */

#endif /* BLOCK_ALLOCATION */

  int numusers;           /* number of users in the channel */
  int modes;              /* channel modes */
  int limit;              /* 0 if no limit */
  struct ChannelUser *firstuser; /* pointer to first user in channel */
  time_t since;           /* when the channel was created (TS) */
  struct ChannelBan *firstban; /* pointer to first ban */
  struct ChannelGecosBan *firstgecosban; /* pinter to first gecos field ban*/
  struct Exception *exceptlist; /* pointer to first ban exception */

  /*
   * flood_ts[0] is the TS of the first time a *Serv was kicked;
   * flood_ts[1] is the TS of the last time
   */
  time_t flood_ts[2];
  int floodcnt;           /* how many times a *Serv was kicked/deoped */
};

/*
 * Prototypes
 */

void AddGecosBan(char *, struct Channel *, char *);
void DeleteGecosBan(struct Channel *, char *);

void AddBan(char *, struct Channel *, char *);
void DeleteBan(struct Channel *, char *);
void AddException(char *, struct Channel *, char *);
void DeleteException(struct Channel *, char *);
struct Channel *AddChannel(char **, int, char **);
void DeleteChannel(struct Channel *);
void AddToChannel(struct Channel *, char *);
void RemoveNickFromChannel(char *, char *);
void RemoveFromChannel(struct Channel *, struct Luser *);
void UpdateChanModes(struct Luser *lptr, char *source,
                     struct Channel *chptr, char *modes);
struct UserChannel *FindChannelByUser(struct Luser *lptr,
                                      struct Channel *chptr);
struct ChannelUser *FindUserByChannel(struct Channel *chptr,
                                      struct Luser *lptr);
void DoMode(struct Channel *, char *, int);
void SetModes(char *source, int plus, char mode,
              struct Channel *chptr, char *args);
void KickBan(int, char *, struct Channel *, char *, char *);
struct Channel *IsChan(char *channel);
int IsChannelMember(struct Channel *chptr, struct Luser *lptr);
int IsChannelVoice(struct Channel *chptr, struct Luser *lptr);
int IsChannelOp(struct Channel *chptr, struct Luser *lptr);
struct ChannelBan *MatchBan(struct Channel *, char *);
struct ChannelBan *FindBan(struct Channel *, char *);
struct Exception *MatchException(struct Channel *, char *);
struct Exception *FindException(struct Channel *, char *);

struct ChannelGecosBan *MatchGecosBan(struct Channel *, char *);
struct ChannelGecosBan *FindGecosBan(struct Channel *, char *);

/*
 * External declarations
 */

extern struct Channel *ChannelList;

#endif /* INCLUDED_channel_h */