/*
 * =====================================================================================
 *       Filename:  who.c
 *    Description:  实现who的功能
 *        Version:  1.0
 *        Created:  2015年09月18日 08时01分28秒
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 * =====================================================================================
 */
#include	<stdlib.h>
#include    <stdio.h>
#include <unistd.h>
#include <utmp.h>
#include <fcntl.h>
#include <time.h>
#define SHOWHOST

void show_info(struct utmp * utmpfp);
/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
int main ( int argc, char *argv[] )
{
    struct utmp current_reccord;
    int utmpfd;
    int reclen = sizeof(current_reccord);
    if((utmpfd = open(UTMP_FILE,O_RDONLY))==-1){
        perror(UTMP_FILENAME);
        exit(1);
    }
    while(read(utmpfd,&current_reccord,reclen)==reclen){
        show_info(&current_reccord);
    }
    close(utmpfd);
    return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
void show_info(struct utmp * utmpfp){
    if(utmpfp->ut_type != USER_PROCESS)
        return ;
    printf("%-8.8s",utmpfp->ut_name);
    printf(" ");
    printf("%-8.8s",utmpfp->ut_line);
    printf(" ");
    printf("%-16.16s",ctime(&utmpfp->ut_time));
    printf(" ");
#ifdef SHOWHOST
    if(utmpfp->ut_host[0]!='\0')
        printf("(%s)",utmpfp->ut_host);
#endif
    printf("\n");
}
