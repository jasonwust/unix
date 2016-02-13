/*
 * =====================================================================================
 *       Filename:  echosrv.c
 *    Description:  echo server
 *        Version:  1.0
 *        Created:  2015年11月07日 12时48分29秒
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 * =====================================================================================
 */

#include	<stdlib.h>
#include    <stdio.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
int main ( int argc, char *argv[] )
{
    fd_set fds;
    int listenfd,maxfd,maxi=-1,client[FD_SETSIZE],i,n;
    char buf[1024];
    struct sockaddr_in server;
    bzero(&server,sizeof(server));
    listenfd = socket(AF_INET,SOCK_STREAM,0);
    server.sin_family = AF_INET;
    server.sin_port = htons(8080);
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    bind(listenfd,(struct sockaddr *)&server,sizeof(server));
    listen(listenfd,20);

    maxfd  = listenfd;
    FD_ZERO(&fds);
    FD_SET(listenfd,&fds);
    for(i=0;i<FD_SETSIZE;i++){
        client[i] = -1;
    }
    struct timeval timeout = {2,0};
    while(1){
        int nready = select(maxfd+1,&fds,NULL,NULL,&timeout);
        if(FD_ISSET(listenfd,&fds)){
            for(i=0;i<FD_SETSIZE;i++){
                if(client[i]<0){
                    client[i] = accept(listenfd,NULL,NULL);
                    break;
                }
            }
            if(i==FD_SETSIZE){
                perror("too many client");
                exit(EXIT_FAILURE);
            }
            FD_SET(client[i],&fds);
            if(client[i]>maxfd){
                maxfd = client[i];
            }
            if(i>maxi)
                maxi = i;
            if(--nready<=0){
                continue;
            }
        }

        for(i=0;i<maxi;i++){
            if(client[i]<0){
                continue;
            }
            if(FD_ISSET(client[i],&fds)){
                if((n=read(client[i],buf,sizeof(buf)))==0){
                    close(client[i]);
                    FD_CLR(client[i],&fds);
                    client[i] = -1;
                }else
                    write(client[i],buf,n);
                if(--nready<=0)
                    break;
            }
        }
    }

    return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
