/*
 * =====================================================================================
 *       Filename:  webserver.c
 *    Description:  简单的web 服务器
 *        Version:  1.0
 *        Created:  2015年10月13日 22时07分50秒
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 * =====================================================================================
 */


#include	<stdlib.h>
#include    <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <pthread.h>
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
    int server_fd,maxfd,maxi,n,i,client[FD_SETSIZE];
    fd_set allfd;
    struct sockaddr_in seraddr;
    memset(&seraddr,0.sizeof(aeraddr));
    seraddr.sin_family = AF_INET;
    seraddr.sin_port = htons(8080);
    seraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  handle_thread
 *  Description:  
 * =====================================================================================
 */
void *handle_thread (void *arg)
{
    int connfd = *(int*)arg;
    int sizet;
    char buffer[1024];
    char str[] = "<h1>helo world</h1>";
    if(send(connfd,str,sizeof(str),0)<0){
       perror("write error");
    }
    if((sizet=recv(connfd,buffer,1023,MSG_DONTWAIT)<0)){
        perror("recv error");
        exit(EXIT_FAILURE);
    }
    buffer[sizet] = '\0';
    printf("recv msg:%s",buffer);
    pthread_exit("handle end");
    return NULL;
}		/* -----  end of function handle_thread  ----- */

