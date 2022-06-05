#include "config.h"
#include "app_thread.h"
#include "app_timer.h"
#include "app_char.h"



int main(){
    user_thread_init();
    user_timer_init();
    user_char_open();
    user_char_ioctl();
    printf("loading init thread!\n");
    while(1);
    return 0;
}




