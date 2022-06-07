#include "core_thread.h"


#define CLONE_KERNEL    (CLONE_FS | CLONE_FILES | CLONE_SIGHAND)

struct task_struct *task1_handle = NULL;
struct task_struct *task2_handle = NULL;

int kernel_count1(void *arg){
    static int n = 1;
    // while(1){
    //     if(kthread_should_stop())
    //     {
    //         break;
    //     }
    //     printk("kthread1 running\n");
    //     ssleep(3);
    // }
    
    while(1){
        if(kthread_should_stop())
        {
            break;
        }
        printk("kthread1 running!!!\n");
        // ssleep(3);
        while(timer_flag1);

        timer_flag1 = 1;
        printk("num1:%d\n",n++);
        if(n > 100){
            n = 1;
        }
    }
    return 0;
}
int kernel_count2(void *arg){
    static int n = 1;
    // while(1){
    //     if(kthread_should_stop())
    //     {
    //         break;
    //     }
    //     printk("kthread2 running\n");
    //     ssleep(3);


    // }
    
    while(1){
        if(kthread_should_stop())
        {
            break;
        }
        printk("kthread2 running!!!\n");
        // ssleep(3);

        while(timer_flag2);
        timer_flag2 = 1;
        
        printk("num2:%d\n",n++);
        if(n > 100){
            n = 1;
        }
    
    }
    return 0;
}

int count_thread_init()
{
    printk("Thread Init...\n");
    task1_handle = kthread_run(kernel_count1,NULL,"count1 task");  
    task2_handle = kthread_run(kernel_count2,NULL,"count2 task");  
    if(IS_ERR(task1_handle) || IS_ERR(task2_handle)){
        kthread_stop(task1_handle);
        kthread_stop(task2_handle);
    }
    return 0;
}

void count_thread_exit()
{
    printk("Thread Exit...\n");
    kthread_stop(task1_handle);
    kthread_stop(task2_handle);
}
