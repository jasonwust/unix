/*
 * =====================================================================================
 *       Filename:  3_12.c
 *    Description:  unix 环境编程第三章示例代码3-12
 *        Version:  1.0
 *        Created:  2015年06月03日 16时18分18秒
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

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  set_fl
 *  Description:  在原来的问爱你描述符基础上加上新的标识
 * =====================================================================================
 */
void set_fl (int fd,int flags)
{
    int val;
    if((val = fcntl(fd,F_GETFL,0)) <0)
        ERR_EXIT("fctnl error");
    val |= flags;
    if(fcntl(fd,F_SETFL,val) <0)
        ERR_EXIT("fcntl error");
    return ;
}		/* -----  end of function set_fl  ----- */
/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  修改文件描述符
 * =====================================================================================
 */
int main ( int argc, char *argv[] )
{

    return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
