/* pxc180001
 * start lottery scheduler
 * */

#ifndef _PSTAT_H
#define _PSTAT_H
#include "param.h"
enum procstate { UNUSED, EMBRYO, SLEEPING, RUNNABLE, RUNNING, ZOMBIE };
struct pstat {
_Bool inuse[NPROC];
int pid[NPROC];
int ticks[NPROC];
int tickets[NPROC];
enum procstate state[NPROC];
int total_tickets;
};
#endif

