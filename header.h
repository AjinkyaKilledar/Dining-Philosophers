#ifndef HEADER_H
#define HEADER_H

#include <errno.h>
#include <signal.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <time.h>
#include <unistd.h>


#define PHILOSOPHER_COUNT 5
#define TOTAL_MEALS 4


extern int semaphore_id;


/*
 * Required union for System V semaphore control operations.
 */
union semun
{
    int val;
    struct semid_ds *buf;
    unsigned short *array;
    struct seminfo *__buf;
};

#endif