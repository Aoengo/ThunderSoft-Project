#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/version.h>
#include <linux/fs.h>
#include <linux/fcntl.h>
#include <linux/ctype.h>
#include <linux/cdev.h>
#include <linux/slab.h>
#include <linux/vmalloc.h>
#include <linux/pagemap.h>
#include <linux/errno.h>
#include <linux/types.h>

#define BUF_SIZE        256

#define DEMO_MAJOR      240
#define DEMO_MINOR      0

#define COMMAND_A 'a'
#define COMMAND_B 'b'

struct demo_dev {
    struct cdev cdev;
};


static struct demo_dev *demo_devices;
static unsigned char demo_count = 0;
static u8 demo_buf[BUF_SIZE];


static loff_t demo_llseek(struct file *filp,loff_t off,int whence){
    loff_t pos = filp->f_pos;
    printk(KERN_ERR "DEMO: Line %d,function %s() has been invoked!\n",__LINE__,__func__);
    switch(whence){
        case 0:
            pos = off;
            break;
        case 1:
            pos +=off;
            break;
        case 2:
        default:
            return -EFAULT;
    }
    if((pos > BUF_SIZE) || (pos < 0)){
        return -EINVAL;
    }
    return filp->f_pos = pos;
}

static ssize_t demo_read(struct file *filp,char __user *buf,size_t count,loff_t *f_pos){
    ssize_t retval = 0;
    loff_t pos = *f_pos;
    printk(KERN_ERR "DEMO: Line %d,function %s() has been invoked!\n",__LINE__,__func__);
    if(pos > BUF_SIZE){
        printk(KERN_ERR "DEMO: Line %d,pos is overflow!\n",__LINE__);
        count = -EINVAL;
        goto out;
    }   
    if(count > (BUF_SIZE - pos)){
        count = BUF_SIZE -pos;
    }
    pos += count;
    if(copy_to_user(buf,demo_buf + *f_pos,count)){
        count = -EFAULT;
        goto out;
    }
    *f_pos = pos;
    retval = count;
out:
    return retval;
}


static ssize_t demo_write(struct file *filp, const char __user *buf,size_t count,loff_t *f_pos){
    ssize_t retval = 0;
    loff_t pos = *f_pos;
    printk(KERN_ERR "DEMO: Line %d,function %s() has been invoked!\n",__LINE__,__func__);
    if(pos > BUF_SIZE){
        printk(KERN_ERR "DEMO: Line %d,pos is overflow!\n",__LINE__);
        count =-EINVAL;
        goto out;
    }
    if(count > (BUF_SIZE - pos)){
        count = BUF_SIZE - pos;
    }
    pos += count;
    if(copy_from_user(demo_buf + *f_pos,buf,count)){
        count = -EFAULT;
        goto out;
    }
    *f_pos = pos ;
    retval = count;
out:
    return retval;
}

static long demo_ioctl(struct file *filp,unsigned int cmd,unsigned long arg){
    printk(KERN_ERR "DEMO: Line %d,function %s() has been invoked!\n",__LINE__,__func__);
    switch(cmd){
        case COMMAND_A:
            printk("DEMO:Line %d,ioctl successfully(COMMAND_A)!\n",__LINE__);
            break;
        case COMMAND_B:
            printk("DEMO:Line %d,ioctl successfully(COMMAND_B)!\n",__LINE__);
            break;
        default:
            printk("DEMO:Line %d,ioctl error(invalid command)!\n",__LINE__);
            return -EINVAL;
    }
    return 0;
}


static int demo_open(struct inode *inode,struct file *filp){
    struct demo_dev *dev;
    printk(KERN_ERR "DEMO: Line %d,function %s() has been invoked!\n",__LINE__,__func__);
    if(demo_count > 0){
        return -EINVAL;
    }
    demo_count++;
    dev = container_of(inode->i_cdev,struct demo_dev,cdev);
    filp->private_data = dev;
    return 0;
}

static int demo_release(struct inode *inode,struct file *filp){
    printk(KERN_ERR "DEMO: Line %d,function %s() has been invoked!\n",__LINE__,__func__);
    demo_count--;
    return 0;
}

static struct file_operations demo_fops = {
    .owner          = THIS_MODULE,
    .llseek         = demo_llseek,
    .read           = demo_read,
    .write          = demo_write,
    .unlocked_ioctl = demo_ioctl,
    .open           = demo_open,
    .release        = demo_release,
};


static int __init control_init(void){
    int retval;
    dev_t devno = 0;
    printk(KERN_ERR "DEMO: Line %d, function %s() has been invoked!\n",__LINE__, __func__);
    devno = MKDEV(DEMO_MAJOR,DEMO_MINOR);
    printk(KERN_ERR "DEMO: Line %d, major = %d, minor = %d\n",__LINE__, MAJOR(devno), MINOR(devno));
    retval = register_chrdev_region(devno,1,"demo_control");
    if(retval){
        printk(KERN_ERR "DEMO: Line %d, failed to register char_dev demo_test!\n",__LINE__);
        goto out;
    }
    demo_devices = kmalloc(sizeof(struct demo_dev),GFP_KERNEL);
    if(!demo_devices){
        retval = -ENOMEM;
        goto error_cdev;
    }
    memset(demo_devices,0,sizeof(struct demo_dev));
    cdev_init(&demo_devices->cdev,&demo_fops);
    demo_devices->cdev.owner = THIS_MODULE;
    demo_devices->cdev.ops = &demo_fops;
    
    retval = cdev_add(&demo_devices->cdev,devno,1);

    if(retval){
        printk(KERN_ERR "DEMO: Line %d,failed to add char_dev demo_test!\n",__LINE__);
        goto error_cdev;
    }
out:
    return retval;

error_cdev:
    if(demo_devices){
        cdev_del(&demo_devices->cdev);
        kfree(demo_devices);
    }
    unregister_chrdev_region(devno,1);
    return retval;
}

static void __exit control_exit(void){
    dev_t devno = MKDEV(DEMO_MAJOR,DEMO_MINOR);
    printk(KERN_ERR "DEMO: Line %d,function %s() has been invoked!\n",__LINE__,__func__);
    if(demo_devices){
        cdev_del(&demo_devices->cdev);
        kfree(demo_devices);
    }
    unregister_chrdev_region(devno,1);
}



module_init(control_init);
module_exit(control_exit);

MODULE_AUTHOR("Gabriel");
MODULE_LICENSE("Dual BSD/GPL");
MODULE_DESCRIPTION("Kernel module");


