#include "core_char.h"



#define DEMO_MAJOR      236
#define DEMO_MINOR      0

#define COMMAND_A 'a'
#define COMMAND_B 'b'


static long demo_ioctl(struct file *filp,unsigned int cmd,unsigned long arg){
    printk(KERN_ERR "DEMO: Line %d,function %s() has been invoked!\n",__LINE__,__func__);
    switch(cmd){
        case COMMAND_A:
            printk("DEMO: Line %d,ioctl successfully(COMMAND_A)!\n",__LINE__);
            break;
        case COMMAND_B:
            printk("DEMO: Line %d,ioctl successfully(COMMAND_B)!\n",__LINE__);
            break;
        default:
            printk("DEMO: Line %d,ioctl error(invalid command)!\n",__LINE__);
            return -EINVAL;
    }
    return 0;
}


static struct file_operations demo_fops = {
    .owner          = THIS_MODULE,
    // .llseek         = demo_llseek,
    // .read           = demo_read,
    // .write          = demo_write,
    .unlocked_ioctl = demo_ioctl,
    // .open           = demo_open,
    // .release        = demo_release,
};

int core_char_init(){
    int retval;

    dev_t devno = 0;

    devno = MKDEV(DEMO_MAJOR,DEMO_MINOR);

    retval = register_chrdev_region(devno,1,"demo_char");
    if(retval){
        printk("Character Device Register Failed!\n");
        goto out;
    }
    cdev_init(&dev.cdev,&demo_fops);

    dev.cdev.owner = THIS_MODULE;
    dev.cdev.ops = &demo_fops;

    retval = cdev_add(&dev.cdev,devno,1);
    if(retval){
        printk("Character Device Add Failed!\n");
        goto err;
    }
    printk("Character Device Add Successfully!\n");
out:
    return 1;

err:
    cdev_del(&dev.cdev);
    unregister_chrdev_region(devno,1);
    return 0;    
}

void core_char_exit(){
    dev_t devno = MKDEV(DEMO_MAJOR,DEMO_MINOR);
    cdev_del(&dev.cdev);
    unregister_chrdev_region(devno,1);
}