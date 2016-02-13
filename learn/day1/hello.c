/*
 * =====================================================================================
 *       Filename:  hello.c
 *    Description:  编译hello.c
 *        Version:  1.0
 *        Created:  2015年10月15日 19时21分09秒
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
    printf("hello world!\n");
    int fa(int,int);
    int r = fa(10,20);
    printf("r=%d\n",r);
    double fb(double,double);
    double r2=fb(3.14,4.15);
    printf("r2=%f\n",r2);
#line 1
    return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */

