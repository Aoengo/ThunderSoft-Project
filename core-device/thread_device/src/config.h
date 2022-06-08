#ifndef __CONFIG_H_
#define __CONFIG_H_

#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/init.h>
#include <linux/kmod.h>
#include <linux/sched.h>
#include <linux/delay.h>
#include <linux/kthread.h>
#include <linux/time.h>
#include <linux/semaphore.h>




typedef struct {
    struct semaphore thread_sema;
    struct semaphore timer_sema;
    int num1;
    int num2;
    int thread_state;
}core_dev_t;

extern core_dev_t dev;
#endif 