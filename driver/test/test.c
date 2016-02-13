/*
 * =====================================================================================
 *       Filename:  test.c
 *    Description:  测试模块
 *        Version:  1.0
 *        Created:  2016年02月04日 12时56分53秒
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 * =====================================================================================
 */
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include "add_sub.h"

static long a =1;
static long b =1;
static int AddOrSub = 1;
static int test_init(void)
{
    long result =0 ;
    printk(KERN_ALERT "test init\n");
    if(AddOrSub == 1)
    {
        result = add_integer(a,b);
    }else{
        result = sub_integer(a,b);
    }
    printk(KERN_ALERT "the %s result is %ld",AddOrSub == 1?"Add":"Sub",result);
    return 0;
}
static void test_exit(void)
{
    printk(KERN_ALERT "test exit\n");
}
module_init(test_init);
module_exit(test_exit);
module_param(a,long,S_IRUGO);
module_param(b,long,S_IRUGO);
module_param(AddOrSub,int,S_IRUGO);

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("jason");
MODULE_DESCRIPTION("A module for testing module params  and export_symbol");
MODULE_VERSION("V1.0");


