#include "core_semaphore.h"


void thread_sema_init(){
    sema_init(&dev.timer_sema,0);
    sema_init(&dev.thread_sema,0);
}