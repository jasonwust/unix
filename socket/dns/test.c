/*
 * =====================================================================================
 *       Filename:  test.c
 *    Description:  test
 *        Version:  1.0
 *        Created:  2015年11月26日 01时22分03秒
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
    char str[12]="hello world";
    char *pstr = str;
    while(*pstr++){
        printf("%c",*pstr);
    }
    return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
