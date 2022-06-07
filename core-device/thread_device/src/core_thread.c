#include "core_thread.h"


#define CLONE_KERNEL    (CLONE_FS | CLONE_FILES | CLONE_SIGHAND)

struct task_struct *task1_handle = NULL;
struct task_struct *task2_handle = NULL;

int kernel_count1(void *arg){
    static int n = 1;
    while(1){
        // printk("%s: %d\n",__func__,n++);
        // ssleep(3);
        // if(kthread_should_stop())
        // {
        //     break;
        // }
        if(num_value.ready1){
            num_value.ready1 = 0;
            printk("num:%d\n",n++);
            if(n > 100){
                n = 1;
            }
        }
    }
    return 0;
}
int kernel_count2(void *arg){
    static int n = 1;
    while(1){
        // printk("%s: %d\n",__func__,n++);
        // ssleep(3);
        // if(kthread_should_stop())
        // {
        //     break;
        // }
        if(num_value.ready2){
            num_value.ready2 = 0;
            printk("num:%d\n",n++);
            if(n > 100){
                n = 1;
            }
        }
    }
    return 0;
}

int count_thread_init(void)
{
    printk("Thread Init...\n");
    task1_handle = kthread_create(kernel_count1,NULL,"count1 task");  
    task2_handle = kthread_create(kernel_count2,NULL,"count2 task");  
    if(!IS_ERR(task1_handle) && !IS_ERR(task2_handle)){
        wake_up_process(task1_handle);
        wake_up_process(task2_handle);
    }else {
        kthread_stop(task1_handle);
        kthread_stop(task2_handle);
    }
    return 0;
}

void count_thread_exit(void)
{
    printk("Thread Exit...\n");
    kthread_stop(task1_handle);
    kthread_stop(task2_handle);
}
