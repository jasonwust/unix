/*
 * =====================================================================================
 *       Filename:  brocastdg_cli.c
 *    Description:  广播请求的回射程序
 *        Version:  1.0
 *        Created:  2015年09月17日 17时19分43秒
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
    return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  dg_cli
 *  Description:  
 * =====================================================================================
 */
void dg_cli (File *fp,int sockfd,const sockadd *addr,socklen_t serlen )
{
    int n;
    const int on =1;
    char sendline[MAXLINE],recvline[MAXLINE+1];
    socklen_t len;
    struct sockaddr * preply_addr;
    setsockopt(sockfd,SOL_SOCK,SO_BROADCAST,&on,sizeof(on));
    signal(SIGALRM,recvfrom_alarm);
    while(fgets(sendline,MAXLINE,fp)!=NULL){
        semdto(sockfd,sendline,strlen(sendline),0,addr,serlen);
        alarm(5);
        for(;;){
            len = serlen;
            n=recvfrom(sockfd,recvline,MAXLINE,0,preply_addr,&len);
            if(n <0){
                if(errno==EINTR)
                    continue;
                else{
                    perror("recv eroor");
                    exit(EXIT_FAILURE);
                }
            }else{
                recvline[n]=0;
                printf("from %s:%s",sock_ntop_host(preply_addr,len),recvline);
            }
        }
        free(preply_addr);
    }
    return ;
}		/* -----  end of function dg_cli  ----- */
static void recvfrom_alarm(int signo){
    return ;
}
