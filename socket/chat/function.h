/*
 * =====================================================================================
 *       Filename:  function.c
 *    Description:  基础函数库
 *        Version:  1.0
 *        Created:  2015年11月03日 18时58分05秒
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 * =====================================================================================
 */
#ifndef FUNCTION_H
#define FUNCTION_H

#include <unistd.h>

#define ERR_EXIT(name)  do{     \
        perror(#name);          \
        exit(EXIT_FAILURE);         \
}while(0)
#define MAX_SIZE 1024

//从文件描述符中读取n个字符

size_t reandn(int fd,char *buf,int size);
//向文件描述符中写入n个字符

size_t writen(int fd,char*buf,int size);
//从文件描述符中读入一行，以\n结尾

size_t  readLine(int fd,char *buf,int size);

#endif

