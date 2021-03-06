/*
 * =====================================================================================
 *       Filename:  4_3.c
 *    Description:  unix高级环境编程4.3
 *        Version:  1.0
 *        Created:  2015年06月03日 19时16分15秒
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 * =====================================================================================
 */

#include	<stdlib.h>
#include    <stdio.h>
#include <sys/stat.h>
#define ERR_EXIT(name)        \
    do{                         \
        perror(#name);          \
        exit(EXIT_FAILURE);     \
    }while(0)
/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
int main ( int argc, char *argv[] )
{
    int i;
    struct stat buf;
    char *  ptr;
    for (i=1;i<argc;i++){
        printf("%s ",argv[i]);
        if(lstat(argv[i],&buf)<0){
            printf("lstat error\n");
            continue;
        }
        if(S_ISREG(buf.st_mode))
            ptr = "regular";
        else if(S_ISDIR(buf.st_mode))
            ptr = "directory";
        else if(S_ISCHR(buf.st_mode))
            ptr = "character special";
        else if(S_ISBLK(buf.st_mode))
            ptr = "block special";
        else if(S_ISFIFO(buf.st_mode))
            ptr = "fifo";
        else if(S_ISLNK(buf.st_mode))
            ptr = "symbolic link";
        else if(S_ISSOCK(buf.st_mode))
            ptr = "socket";
        else
            ptr = "unknown mode";

        printf("%s\n",ptr);
    }
    return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */



