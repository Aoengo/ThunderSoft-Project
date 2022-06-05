#include "app_thread.h"


volatile num_value_t num_value;


static void* thread1(){
    while(1){
        if(num_value.ready_flag & 0x01){
            num_value.num1 += 1;
            printf("1s count nums:%d\n",num_value.num1); 
            num_value.ready_flag = num_value.ready_flag & 0x02;
        }
    // printf("The first one!\n");
    // sleep(1);
    }
}

static void* thread2(){
    while(1){
        if(num_value.ready_flag & 0x02){
            num_value.num2 += 2;
            printf("2s count nums:%d\n",num_value.num2);
             num_value.ready_flag = num_value.ready_flag & 0x01;
        }
        // sleep(1);
        // printf("The second one\n");
    }
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

