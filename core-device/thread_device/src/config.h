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
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>



#define BUF_SIZE        256

typedef struct {
    //character device
    struct cdev cdev;
    uint8_t demo_buf[BUF_SIZE];

    //semaphore
    struct semaphore timer_sema1;
    struct semaphore timer_sema2;

    //count numbers
    int num1;
    int num2;

    //thread work state
    int thread_state;
}core_dev_t;

extern core_dev_t dev;
#endif 