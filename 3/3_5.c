/*
 * =====================================================================================
 *       Filename:  3_5.c
 *    Description:  unix 环境编程第三章示例代码3-5
 *        Version:  1.0
 *        Created:  2015年06月01日 23时05分18秒
 *       Compiler:  gcc
 *         Author:  jason
 * =====================================================================================
 */


#include	<stdlib.h>
#include    <stdio.h>

#include <error.h>
#include <unistd.h>

#define    ERR_EXIT(name)    \
    do {                       \
        perror(#name);     \
        exit(EXIT_FAILURE);  \
    }while(0);

#define BUFSIZE  4096
/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description: 使用read 和 write 复制一个文件
 * =====================================================================================
 */
int main ( int argc, char *argv[] )
{
    int n;
    char buf[BUFSIZE];
    while((n = read(STDIN_FILENO,buf,BUFSIZE)) >0 ){
        if(write(STDOUT_FILENO,buf,n) != n )
            ERR_EXIT("写入出错");

    }
    if(n <0 )
        ERR_EXIT("读入数据出错");
    return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
