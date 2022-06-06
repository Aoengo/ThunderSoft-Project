#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/init.h>
#include <linux/kmod.h>
#include <linux/sched.h>
#include <linux/delay.h>
#include <linux/kthread.h>



#define CLONE_KERNEL    (CLONE_FS | CLONE_FILES | CLONE_SIGHAND)

struct task_struct *task1_handle = NULL;
struct task_struct *task2_handle = NULL;

int kernel_count1(void *arg){
    static int n = 0;
    while(1){
        printk("%s: %d\n",__func__,n++);
        ssleep(3);
        if(kthread_should_stop())
        {
            break;
        }
    }
    return 0;
}
int kernel_count2(void *arg){
    static int n = 0;
    while(1){
        printk("%s: %d\n",__func__,n++);
        ssleep(3);
        if(kthread_should_stop())
        {
            break;
        }
    }
    return 0;
}

static int __init count_thread_init(void)
{
    printk("%s:\n",__func__);
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

static void __exit count_thread_exit(void)
{
        printk("%s:\n",__func__);
        kthread_stop(task1_handle);
        kthread_stop(task2_handle);
}

MODULE_AUTHOR("Gabriel");
MODULE_LICENSE("GPL");

module_init(count_thread_init);
module_exit(count_thread_exit);
