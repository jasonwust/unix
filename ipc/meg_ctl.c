/*
 * =====================================================================================
 *       Filename:  1.c
 *    Description:  ipc learn
 *        Version:  1.0
 *        Created:  2015年07月06日 18时13分52秒
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 * =====================================================================================
 */


#include	<stdlib.h>
#include    <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 *
 *
 * ipcs 查看ipc对象
 * ipcrm 删除ipc对象
 */
int main ( int argc, char *argv[] )
{
    int msgid;
    //msgid = msgget(1234,0666 | IPC_CREAT);
    msgid = msgget(IPC_PRIVATE,0666);   //创建私有的消息队列
    if(msgid == -1){
        perror("msgget error");
        exit(EXIT_FAILURE);
    }
    printf("msgget succ\n");
    struct msqid_ds buf;
    msgctl(msgid,IPC_STAT,&buf);
    printf("mode:%o\n",buf.msg_perm.mode);
    printf("bytes=%ld\n",buf.__msg_cbytes);
    printf("number=%d\n"buf.msg_qnum);
    printf("msgmax=%d\n",buf.msg_qbytes);
    //更改权限
    sscanf("600","%o",(unsigned int)&buf.msg_prem.mode);

    msgctl(msgid,IPC_SET,&buf)

    return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */

