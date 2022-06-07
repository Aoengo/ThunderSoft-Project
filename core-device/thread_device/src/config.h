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


typedef struct{
    unsigned short ready1;
    unsigned short ready2;
    int num1;
    int num2;
}num_value_t;

extern volatile num_value_t num_value;



#endif 