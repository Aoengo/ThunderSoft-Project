#include "config.h"
#include "core_thread.h"
#include "core_timer.h"





static int __init user_module_init(void){
    count_timer_init();
    count_thread_init();
    return 0;
}
static void __exit user_module_exit(void){
    count_timer_exit();
    count_thread_exit();
}

MODULE_AUTHOR("Gabriel");
MODULE_LICENSE("GPL");

module_init(user_module_init);
module_exit(user_module_exit);


