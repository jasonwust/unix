/*
 * =====================================================================================
 *       Filename:  malloc.c
 *    Description:  malloc 使用
 *        Version:  1.0
 *        Created:  2015年11月07日 11时50分35秒
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
    char str1[] ="哈哈hah";
    printf("%d,%d\n",strlen(str1),sizeof(str1));
    char str2[10];
    bzero(str2,sizeof(str2));
    strcpy(str2,str1);
    printf("%s,%d\n",str2,strlen(str2));


    char * str = (char *)malloc(strlen(str1)+1);
    memcpy(str,str1,strlen(str1));
    str[strlen(str1)] ='\0';
    printf("strlen=%d,str=%s\n",sizeof(str),str);

    return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
