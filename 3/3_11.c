/*
 * =====================================================================================
 *       Filename:  3_11.c
 *    Description:  unix 环境编程第三章示例代码3-11
 *        Version:  1.0
 *        Created:  2015年06月03日 12时48分18秒
 *       Compiler:  gcc
 *         Author:  jason
 * =====================================================================================
 */


#include	<stdlib.h>
#include    <stdio.h>

#include <error.h>
#include <unistd.h>
#include <fcntl.h>
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
    int val;
    if(argc != 2)
        ERR_EXIT("参数个数不对");
    if((val = fcntl(atoi(argv[1]),F_GETFL,0)) < 0)
        ERR_EXIT("获取文件标识符的文件标志出错");
    switch( val & O_ACCMODE){
        case O_RDONLY:
            printf("read");
            break;
        case O_WRONLY:
            printf("write");
            break;
        case O_RDWR:
            printf("read and write");
            break;
        default:
            ERR_EXIT("未知标志类型");
    }
    if(val & O_APPEND)
        printf(",append");
    if(val & O_NONBLOCK)
        printf(", 非阻塞模式");
    if(val & O_SYNC)
        printf(", 等待写完成(数据和属性)");

    putchar('\n');
    return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
