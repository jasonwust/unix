/*
 * =====================================================================================
 *       Filename:  3_1.c
 *    Description:  unix 环境编程第三章示例代码3-1
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
/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description: 用于验证标准输入能否设置偏移量
 * =====================================================================================
 */
int main ( int argc, char *argv[] )
{
    if(lseek(STDIN_FILENO,0,SEEK_CUR)==-1){
        ERR_EXIT("标准输入不能设置偏移量");
    }
    else
        printf("ok");
    return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
