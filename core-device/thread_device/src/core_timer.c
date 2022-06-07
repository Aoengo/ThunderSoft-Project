#include "core_timer.h"

volatile unsigned short timer_flag1 = 1;
volatile unsigned short timer_flag2 = 1;

static struct timer_list timer;

void timer_callback(struct timer_list *t){
    printk("Timer running");
    timer_flag1 = 0;
    timer_flag2 = 0;
    mod_timer(&timer,jiffies + msecs_to_jiffies(1000));
}

int count_timer_init(void){
    //old kernel version
    // init_timer(&timer);
    // timer.function = (void *)timer_callback;
    // timer.expires = jiffies + 1000;
    // timer.data = 0;
    // add_timer(&timer);
    timer_setup(&timer,timer_callback,0);
    add_timer(&timer);
    printk("Timer Init...\n");
    return 0;
}

void count_timer_exit(void){
    printk("Timer Exit...\n");
    del_timer(&timer);
}