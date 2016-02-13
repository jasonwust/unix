/*
 * =====================================================================================
 *       Filename:  daytimetcpcli1.c
 *    Description:  连接时间服务的client客户端
 *        Version:  1.0
 *        Created:  2015年09月16日 18时54分35秒
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 * =====================================================================================
 */


#include	<stdlib.h>
#include    <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
int main ( int argc, char *argv[] )
{
    int connfd;
    struct sockaddr_in serveraddr;
    char buff[1024];
    memset(&serveraddr,0,sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = INADDR_ANY;
    serveraddr.sin_port = htons(13);
    if((connfd = socket(AF_INET,SOCK_STREAM,0))<0){
        perror("socket error");
        exit(EXIT_FAILURE);
    }
    if(connect(connfd,(struct sockaddr *)&serveraddr,sizeof(serveraddr))<0){
        perror("socket error");
        exit(EXIT_FAILURE);
    }
    read(connfd,buff,sizeof(buff));
    printf("now time is %s",buff);
    close(connfd);
    return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */

