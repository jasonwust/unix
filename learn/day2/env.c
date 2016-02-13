/*
 * =====================================================================================
 *       Filename:  env.c
 *    Description:  print env
 *        Version:  1.0
 *        Created:  2015年10月15日 19时33分20秒
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 * =====================================================================================
 */

#include	<stdlib.h>
#include    <stdio.h>
#include <string.h>
/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
int main ( int argc, char *argv[] )
{
    extern char ** environ;
    printf("environ=%p\n",environ);
    char ** env = environ;
    while(*env!=NULL){
        printf("%s\n",*env++);
    }
    return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
