/*
 * =====================================================================================
 *       Filename:  hostbyteorder.c
 *    Description:  确定系统字节序
 *        Version:  1.0
 *        Created:  2015年09月16日 16时32分52秒
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 * =====================================================================================
 */

#include	<stdlib.h>
#include    <stdio.h>
/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
int main ( int argc, char *argv[] )
{
    union {
        short s;
        char c[sizeof(short)];
    }un;
    un.s = 0x0102;
    if(sizeof(short)==2){
        if(un.c[0]==1 && un.c[1]==2){
            printf("big-endian\n");
        }else if(un.c[0]==2 && un.c[1]==1){
            printf("little-enbdain\n");
        }else{
            printf("unkown");
        }
    }else{
        printf("short size = %d\n",sizeof(short));
    }
    return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */

