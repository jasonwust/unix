/*
 * =====================================================================================
 *       Filename:  hello.c
 *    Description:  a simplest module
 *        Version:  1.0
 *        Created:  2015年12月27日 12时33分44秒
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 * =====================================================================================
 */
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
MODULE_LICENSE("Dual BSD/GPL");
static int hello_init(void)
{
    printk("hello world\n");
    return 0;
}

static void hello_exit(void)
{
    printk("Goodbye world\n");
}
module_init(hello_init);
module_exit(hello_exit);
