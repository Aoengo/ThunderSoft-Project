#include "core_timer.h"

volatile num_value_t num_value;

static struct timer_list timer;

void timer_callback(struct timer_list *t){
    static int count = 0;
    num_value.ready1 = 1;
    if(count > 0){
        num_value.ready2 = 1;
        count = 0;
    }else{
        count ++;
    }
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