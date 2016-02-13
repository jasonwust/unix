/*
 * =====================================================================================
 *       Filename:  str_cli.c
 *    Description:  在客户端和服服务器端传输二进制文件
 *        Version:  1.0
 *        Created:  2015年09月17日 07时27分21秒
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 * =====================================================================================
 */

#include	<stdlib.h>
#include    <stdio.h>
#include "util.h"
#define MAX_LINE 1024

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  str_cli
 *  Description:  
 * =====================================================================================
 */
    void
str_cli (FILE *fp,int sockfd )
{
    int maxfdp1;
    fd_set rset;
    char sendLine[MAX_LINE],recvLine[MAX_LINE];
    FD_ZERO(&rset);
    while(1){
        FD_SET(fileno(fp),&rst);
        FD_SET(sockfd,&rst);
        maxfdp1 = max(fileno(fp),sockfd)  +1;
        if(select(maxxfdp1,&rst,NULL,NULL,NULL)==-1){
            perror("select error");
            exit(EXIT_FAILURE);
        }
        if(FD_ISSET(sockfd,&rst)){              //socket is readable
            if(ReadLine(sockfd,recvLine,MAX_LINE)==0){
                perror("str_cli: server teerminated prematurely");
                exit(EXIT_FAILURE);
            }
            fputs(recvline,stdout);
        }
        if(FD_ISSET(fileno(fp),&rst)){          //input is readable
            if(fgets(sendLine,MAX_LINE,fp)==NULL){
                return ;
            }
            writen(sockfd,sendLine,strlen(sendLine));
        }
    }
}		/* -----  end of function str_cli  ----- */
