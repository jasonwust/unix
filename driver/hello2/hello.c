/*
 * =====================================================================================
 *       Filename:  hello.c
 *    Description:  linux 内核编程
 *        Version:  1.0
 *        Created:  2016年02月04日 12时07分41秒
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 * =====================================================================================
 */
#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
MODULE_LICENSE("Dual BSD/GPL");
static int hello_init(void)
{
    printk(KERN_ALERT "hello world\n");
    return 0;
}
static void hello_exit(void)
{
    printk(KERN_ALERT "Goodbye world\n");
}
module_init(hello_init);
module_exit(hello_exit);
