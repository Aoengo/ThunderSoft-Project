#include "config.h"
#include "app_thread.h"
#include "app_timer.h"




int main(){
    user_thread_init();
    user_timer_init();
    printf("loading init thread!\n");
    while(1);
    return 0;
}




