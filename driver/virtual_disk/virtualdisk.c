/*
 * =====================================================================================
 *       Filename:  virtualdisk.c
 *    Description:  虚拟字符驱动程序
 *        Version:  1.0
 *        Created:  2016年02月06日 20时00分52秒
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 * =====================================================================================
 */
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/slab.h>
#include <linux/device.h>
#include <linux/fs.h>
#include <linux/errno.h>
#include <linux/mm.h>
#include <linux/sched.h>
#include <linux/cdev.h>
#include <asm/io.h>
#include <asm/uaccess.h>
#include <linux/semaphore.h>

#define GLOBALMEN_SIZE 0x1000
#define MEM_CLEAR 0x1
#define GLOBALMEM_MAJOR 0

static int globalmem_major = GLOBALMEM_MAJOR;
struct class *module_class = NULL;


//global 设备结构体
struct globalmem_dev{
    struct cdev cdev;
    unsigned char mem[GLOBALMEN_SIZE];//全局内存
    struct semaphore sem;
};
struct globalmem_dev *globalmem_devp;
/* 文件打开函数 */
int globalmem_open(struct inode *inode,struct file *filep){
    /* 将设备结构体指针赋值给文件私有数据指针 */
    filep->private_data = globalmem_devp;
    return 0;
}
int globalmem_release(struct inode *inode,struct file *filep)
{
    return 0;
}
static long globalmem_ioctl(struct file *filep,unsigned int cmd,unsigned long arg)
{
    struct globalmem_dev *dev = filep->private_data;
    switch(cmd){
        case MEM_CLEAR:
            if(down_interruptibale(&dev->sem))
                return -ERESTARTSYS;
            memset(dev->mem,0,GLOBALMEN_SIZE);
            up(&dev->sem);
            printk(KERN_INFO "globalmem is set to zero\n");
            break;
        default:
            return -EINVAL;
    }
    return 0;
}
static ssize_t globalmem_read(struct file *filep,char __user *buf,size_t size,loff_t *ppos)
{
    unsigned long p = *ppos;
    unsigned int count =size;
    int ret=0;
    struct globalmem_dev *dev = filep->private_data;
    if(p>=GLOBALMEN_SIZE)
        return 0;
    if(count > GLOBALMEN_SIZE - p)
        count =GLOBALMEN_SIZE - p;
    if(down_interruptibale(&dev->sem))
        return -ERESTARTSYS;
    if(copy_to_user(buf,(void *)(dev->mem+p),count))
        ret = -EFAULT;
    else{
        *ppos += count;
        ret = count;
        printk(KERN_INFO "read %u bytes(s) from %lu\n",count,p);
    }
    up(&dev->sem);
    return ret;
}
static ssize_t globalmem_write(struct file *filep,const char __user *buf,size_t size,loff_t *ppos)
{
    unsigned long p = *ppos;
    unsigned int count = size;
    int ret = 0;
    struct globalmem_dev *dev = filep->private_data;
    if(p>=GLOBALMEN_SIZE)
        return 0;
    if(count >GLOBALMEN_SIZE)
        count  = GLOBALMEN_SIZE - p;
    if(down_interruptibale(&dev->sem))
    {
        return -ERESTARTSYS;
    }
    if(copy_from_user(dev->mem +p,buf,count))
        ret  = -EFAULT;
    else{
        *ppos+=count;
        ret = count;
        printk(KERN_INFO "write %u bytes from %lu",count,p);
    }

    return ret;
}

static loff_t globalmem_llseek(struct file *filep,loff_t offset,int orig)
{
    int ret=0;
    switch(orig){
        case 0:
            if(offset <0){
                ret = -EINVAL;
                break;
            }
            if((unsigned int )offset > GLOBALMEN_SIZE){
            ret = -EINVAL;
            break;
            }
            filep->f_pos = (unsigned int )offset;
            ret = filep->f_pos;
            break;
       case 1:
            if((filep->f_pos+offset) > GLOBALMEN_SIZE){
                ret = -EINVAL;
                break;
            }
            if((filep->f_pos + offset)<0){
                ret = - EINVAL;
                break;
            }
            filep->f_pos += offset;
            ret = filep->f_pos;
            break;
       default:
            ret = -EINVAL;
            break;
    }
    return ret;
}
static const struct file_operations globalmem_fops = {
    .owner = THIS_MODULE,
    .llseek = globalmem_llseek,
    .read = globalmem_read,
    .write = globalmem_write,
    .unlocked_ioctl = globalmem_ioctl,
    .open = globalmem_open,
    .release = globalmem_release,
};

static void globalmem_setup_cdev(struct globalmem_dev *dev,int index)
{
    int err,devno = MKDEV(globalmem_major,index);
    cdev_init(&dev->cdev,&globalmem_fops);
    dev->cdev.owner = THIS_MODULE;
    err = cdev_add(&dev->cdev,devno,1);
    if(err){
        printk(KERN_NOTICE "Error %d adding globalmem %d",err,index);
    }
    module_class = class_create(THIS_MODULE, "virtualdisk");
    if(module_class==NULL)
    {
        printk(KERN_ALERT "create module_class failed!\n");
        goto fail_create_class;
    }
    device_create(module_class,NULL,MKDEV(globalmem_major,0),NULL,"virtual_disk");
    printk(KERN_ALERT "/dev success");
fail_create_class:
    unregister_chrdev_region(devno,1);
}

int globalmem_init(void)
{
    int result;
    dev_t devno = MKDEV(globalmem_major,0);
    if(globalmem_major)
        result = register_chrdev_region(devno,1,"globalmem");
    else{
        result = alloc_chrdev_region(&devno,0,1,"globalmem");
        globalmem_major = MAJOR(devno);
    }
    if(result < 0 )
        return result;
    globalmem_devp = (struct globalmem_dev *)kmalloc(sizeof(struct globalmem_dev),GFP_KERNEL);
    if(!globalmem_devp){
        result = -ENOMEM;
        goto fail_malloc;
    }
    globalmem_devp->cdev.dev = devno;
    memset(globalmem_devp,0,sizeof(struct globalmem_dev));
    globalmem_setup_cdev(globalmem_devp,0);
    
    sema_init(&globalmem_devp->sem,1);
    return 0;


fail_malloc:
    unregister_chrdev_region(devno,1);
    return result;
}



void globalmem_exit(void)
{
    cdev_del(&globalmem_devp->cdev);
    device_destroy(module_class, MKDEV(globalmem_major, 0));         //delete device node under /dev
    class_destroy(module_class);
    kfree(globalmem_devp);
    unregister_chrdev_region(globalmem_devp->cdev.dev,1);

}
MODULE_LICENSE("Dual BSD/GPL");
module_param(globalmem_major,int,S_IRUGO);

module_init(globalmem_init);
module_exit(globalmem_exit);


