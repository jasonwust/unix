/*
 * =====================================================================================
 *       Filename:  catserver.c
 *    Description:  chat server
 *        Version:  1.0
 *        Created:  2015年10月16日 08时11分00秒
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 * =====================================================================================
 */

#include	<stdlib.h>
#include    <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/select.h>
/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
int main ( int argc, char *argv[] )
{
    struct sockaddr_in server,clientaddr;
    bzero(&server,sizeof(server));
    int listenfd,clientfd;
    listenfd = socket(AF_INET,SOCK_STREAM,0);
    server.sin_family = AF_INET;
    server.sin_port = htons(80);
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    bind(listenfd,(struct sockaddr *)&server,sizeof(server));
    listen(listenfd,20);
    while(1){
        int len = sizeof(clientaddr);
        clientfd = accept(listenfd,(struct sockaddr *)&clientaddr,&len);

    }
    return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */

