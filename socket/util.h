/*
 * =====================================================================================
 *       Filename:  util.h
 *    Description:  提供工具函数的头文件
 *        Version:  1.0
 *        Created:  2015年09月16日 16时54分00秒
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 * =====================================================================================
 */

#ifndef UTIL_H
#define UTIL_H
#include <sys/types.h>
#include <unistd.h>
ssize_t readn(int fd,void *pstr,size_t n);
ssize_t writen(int fd,const void *pstr,size_t n);
ssize_t readLine(int fd,void *pstr,size_t maxlen);
#endif

