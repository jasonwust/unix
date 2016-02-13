/*
 * =====================================================================================
 *       Filename:  daytimetcpsrv1.c
 *    Description:  显示客户端ip地址和端口号的时间获取服务器
 *        Version:  1.0
 *        Created:  2015年09月16日 18时16分05秒
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 * =====================================================================================
 */

#include	<stdlib.h>
#include    <stdio.h>
#include <sys/socket.h>
#include <time.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define ERR_EXIT(name) do{      \
        perror(#name);      \
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
    int listenfd,connfd;
    struct sockaddr_in serveraddr,cliaddr;
    socklen_t len;
    char buff[1024];
    time_t ticks;
    memset(&serveraddr,0,sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serveraddr.sin_port = htons(13);
    if((listenfd  = socket(AF_INET,SOCK_STREAM,0))<0)
        ERR_EXIT("socket error");
    if(bind(listenfd,(struct sockaddr *)&serveraddr,sizeof(serveraddr))<0)
        ERR_EXIT("bind error");
    if(listen(listenfd,5)<0)
        ERR_EXIT("listen error");
    for(;;){
        len = sizeof(cliaddr);
        if((connfd = accept(listenfd,(struct sockaddr*)&cliaddr,&len))<0)
            ERR_EXIT("accept error");
        printf("connection from %s,port %d\n",inet_ntop(AF_INET,&cliaddr.sin_addr.s_addr,buff,sizeof(buff)),
                ntohs(cliaddr.sin_port));
        ticks = time(NULL);
        snprintf(buff,sizeof(buff),"%.24s\r\n",ctime(&ticks));
        if(write(connfd,buff,sizeof(buff))<0)
            ERR_EXIT("write error");
        close(connfd);
    }
    return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */

