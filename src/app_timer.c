#include "app_timer.h"



void timer_handler(){
    printf("Hello\n");
}




void user_timer_init(){
    struct itimerval timer;
    signal(SIGVTALRM,timer_handler);
    timer.it_value.tv_sec = 1;
    timer.it_value.tv_usec = 0;
    timer.it_interval.tv_sec = 1;
    timer.it_interval.tv_usec = 0;
    
    setitimer(ITIMER_VIRTUAL,&timer,NULL);
    printf("Timer Init Successful\n");    
}
