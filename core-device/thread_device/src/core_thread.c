#include "core_thread.h"


#define CLONE_KERNEL    (CLONE_FS | CLONE_FILES | CLONE_SIGHAND)


struct task_struct *task1_handle = NULL;
struct task_struct *task2_handle = NULL;


int kernel_count1(void *arg){
    dev.num1 = 1;
    while(!kthread_should_stop()){
        if(dev.thread_state){
            down(&dev.timer_sema);
            printk("Thread1,num1:%d\n",dev.num1++);
            // printk("kthread1 running!!!\n");
            if(dev.num1 > 100){
                dev.num1 = 1;
            }
            up(&dev.thread_sema);
        }else{
            printk("Waiting Thread1 Exit\n");
            ssleep(1);
        }
        
    }
    return 0;
}
int kernel_count2(void *arg){
    int times = 0;
    dev.num2 = 1;
    while(!kthread_should_stop()){
        if(dev.thread_state){
            down(&dev.thread_sema);
            if(!(times % 2)){
                printk("Thread2,num2:%d\n",dev.num2++);
            }
            if(dev.num2 > 100){
                dev.num2 = 1;
            }
            //
            if(times > 99){
                times = 0;
            }else{
                times ++;
            }
            // printk("kthread2 running!!!\n");

        }else{
            printk("Waiting Thread2 Exit\n");
            ssleep(1);
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
