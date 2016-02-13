/*
 * =====================================================================================
 *       Filename:  pollstr_cli.c
 *    Description:  poll 函数重写版
 *        Version:  1.0
 *        Created:  2015年09月17日 09时20分30秒
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
    int i,maxi,listenfd,connfd,sockfd;
    int nready;
    ssize_t n;
    char buf[1024];
    socklen_t clien;
    struct pollfd client[OPENMAX];
    struct sockaddr_in cliaddr,seraddr;
    listenfd = socket(AF_INET,SOCK_STREAM,0);
    bzero(&seraddr,sizeof(seraddr));
    seraddr.sin_family = AF_INET;
    seraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    seraddr.sin_port = htons(SERV_PORT);
    bind(listenfd,(struct sockaddr *)&seraddr,sizeof(seraddr));
    listen(listenfd,5);
    client[0].fd = listenfd;
    client[0].events = POLLRDNORM;
    for(i=1;i<OPENMAX;i++){
        client[i].fd =-1;
    }
    maxi=0;
    return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */

