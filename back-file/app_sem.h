#ifndef __APP_SEM_H_
#define __APP_SEM_H_



#include "config.h"
#include <sys/sem.h>

#define KEY (key_t)217

typedef union
{
    int val;
    struct semid_ds *buf;
    unsigned short *array;

}sem_u;



#endif

