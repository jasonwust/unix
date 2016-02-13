/*
 * =====================================================================================
 *       Filename:  function.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2015年11月03日 19时00分12秒
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 * =====================================================================================
 */
#include "function.h"

//从文件描述符中读取n个字符
size_t readn(int fd,char *buf,int size){
    int n=0;
    if((n=read(fd,buf,size))!=size){
        return size-n;
    }
    return 0;
}
//向文件描述符中写入n个字符
size_t writen(int fd,char*buf,int size){
    int n=0;
    if((n=write(fd,buf,size))!=size){
        return size-n;
    }
    return 0;
}
//从文件描述符中读入一行，以\n结尾
size_t readLine(int fd,char *buf,int size){
    int i=0;
    while(1){
        readn(fd,buf+i,1);
        if(buf[i++]=='\n' || i==size)
            break;
    }
    return i;
}
