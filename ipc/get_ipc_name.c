/*
 * =====================================================================================
 *       Filename:  get_ipc_name.c
 *    Description:  get_ipc_name
 *        Version:  1.0
 *        Created:  2015年07月09日 20时20分56秒
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 * =====================================================================================
 */

#include	<stdlib.h>
#include    <stdio.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
char * get_ipc_name(const char * name);
/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
int main ( int argc, char *argv[] )
{
    printf("%s\n",get_ipc_name("ipc"));
    return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */



/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  get_ipc_name
 *  Description:  
 * =====================================================================================
 */
char * get_ipc_name (const char * name)
{
    char * dir,*dst,*slash;
    if((dst = (char *)malloc(PATH_MAX))==NULL) return NULL;
    if((dir = getenv("PX_IPC_NAME"))==NULL){
        #ifdef POSIX_IPC_PREFIX
            dir = POSIX_IPC_PREFIX;
        #else
            dir = "/tmp/";
        #endif
    }
    slash = (dir[strlen(dir)-1] == '/') ? "" : "/";
    snprintf(dst,PATH_MAX,"pathname = %s%s%s",dir,slash,name);
    return dst;
}		/* -----  end of function get_ipc_name  ----- */
