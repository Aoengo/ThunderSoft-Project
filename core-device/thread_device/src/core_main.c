#include "config.h"
#include "core_thread.h"
#include "core_timer.h"
#include "core_semaphore.h"
#include "core_char.h"

core_dev_t dev;

static int __init user_module_init(void){
    dev.thread_state = 1;
    thread_sema_init();
    count_timer_init();
    count_thread_init();
    core_char_init();
    return 0;
}
static void __exit user_module_exit(void){
    up(&dev.timer_sema1);
    up(&dev.timer_sema2);
    up(&dev.timer_sema1);
    up(&dev.timer_sema2);
    up(&dev.control_sema); 
    dev.thread_state = 0;
    count_timer_exit();
    count_thread_exit();
    core_char_exit();
    
}

MODULE_AUTHOR("Gabriel");
MODULE_LICENSE("GPL");

module_init(user_module_init);
module_exit(user_module_exit);


