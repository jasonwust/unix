/*
 * =====================================================================================
 *       Filename:  add_sub.c
 *    Description:  add_sub 模块 提供一个加法函数和一个
 *    减法函数
 *        Version:  1.0
 *        Created:  2016年02月04日 12时48分28秒
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 * =====================================================================================
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include "add_sub.h"
long add_integer(long a,long b)
{
    return a+b;
}
long sub_integer(long a,long b)
{
    return a-b;
}
EXPORT_SYMBOL(add_integer); //导出加法函数
EXPORT_SYMBOL(sub_integer);     //导出减法函数
MODULE_LICENSE("Dual BSD/GPL");
