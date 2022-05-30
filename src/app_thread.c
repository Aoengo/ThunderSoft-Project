#include "app_thread.h"





static void* thread1(){
    printf("The first one!\n");
}

static void* thread2(){
    printf("The second one\n");
}







int user_thread_init(){
    pthread_t id1,id2;
    int ret1 = pthread_create(&id1,NULL,thread1,NULL);
    int ret2 = pthread_create(&id2,NULL,thread2,NULL);

    if((ret1 + ret2) != 0){
        printf("Ret:%d Init failed!\n",((ret1 == -1) ? 1 : 2));
        return -1;
    }
    return 0;
}

