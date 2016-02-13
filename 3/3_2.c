/*
 * =====================================================================================
 *       Filename:  3_2.c
 *    Description:  unix 环境编程第三章示例代码3-2
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
#include <fcntl.h>

#define    ERR_EXIT(name)    \
    do {                       \
        perror(#name);     \
        exit(EXIT_FAILURE);  \
    }while(0);


char buf1[] = "abcdefghij";
char buf2[] = "ABCDEFGHIJ";
/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description: 创建一个空洞文件
 * =====================================================================================
 */
int main ( int argc, char *argv[] )
{
    int fd;
    mode_t mode = S_IRUSR | S_IWUSR | S_IROTH ;
    if((fd = creat("file.hole",mode)) < 0){
        ERR_EXIT("create err");
    }
    if(write(fd,buf1,10) != 10){
        ERR_EXIT("buf1 write err");
    }

    if(lseek(fd,16384,SEEK_SET) == -1){
        ERR_EXIT("lseek error");
    }

    if(write(fd,buf2,10) != 10){
        ERR_EXIT("buf2 write err");
    }
    return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
