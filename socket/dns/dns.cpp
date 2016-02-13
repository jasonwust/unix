/*
 * =====================================================================================
 *       Filename:  dns.cpp
 *    Description:  dns 报文主程序
 *        Version:  1.0
 *        Created:  2015年11月21日 14时02分51秒
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 * =====================================================================================
 */

#include	<stdlib.h>
#include    <stdio.h>
#include    <sys/socket.h>
#include    <netinet/in.h>
#include    <arpa/inet.h>
#include    "dns.h"
/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
int main ( int argc, char *argv[] )
{
    if(argc!=2)
        ERR_EXIT("usage dns [name] [ip]");
    int sock;
    struct sockaddr_in seraddr,recvaddr;
    char sendbuf[MAXSIZE],recvbuf[MAXSIZE];
    memset(&seraddr,0,sizeof(seraddr));
    seraddr.sin_family = AF_INET;
    seraddr.sin_port = htons(0);
    seraddr.sin_addr = htonl(INADDR_ANY);
    if((sock = socket(AF_INET,SOCK_DGRAM,0))==-1)
        ERR_EXIT("socket error");
    getDNSHeader(sendbuf);
    getDNSQueryHdr(sendbuf,argv[1]);
    int timeout=300;
    setsockopt(sock,SOL_SOCKET,SO_SNDTIMEO,(void *)timeout,sizeof(int));
    setsockopt(sock,SOL_SOCKET,SO_RCVTIMEO,(void *)timeout,sizeof(int));
    if(sendto(sock,sendbuf,strlen(sendbuf),0,(struct sockaddr*)&seraddr,sizeof(seraddr))==-1)
        ERR_EXIT("send to error");
    if(recvfrom(sock,recvbuf,sizeof(recvbuf),0,(struct sockaddr*)&recvaddr,sizeof(recvaddr))==-1)
        ERR_EXIT("recv error");
    decodeDNSPacket(recvbuf);
    return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  getDNSHeader
 *  Description:  封装一个dns查询报文的头部
 * =====================================================================================
 */
void getDNSHeader (char * buf)
{
    pDNSHDR hdr = (pDNSHDR)buf;
    hdr->type=getpid();
    hdr->sig = htons(0x0100);
    hdr->questionNum = htons(0x0001);
    hdr->resNum= htons(0x0000);
    hdr->authqueNum=htons(0x0000);
    hdr->oqusNum=htons(0x0000);
}		/* -----  end of function getDNSHeader  ----- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  getDNSQueryHdr
 *  Description:  
 * =====================================================================================
 */
void getDNSQueryHdr (char *sendbuf,char *query);
{
    if(inet_addr(query)==INADDR_NONE){                //说明不是一个点分十进制的ip地址，而是一个是域名
        memcpy(sendbuf+sizeof(DNS_HEARDER)+1,query,strlen(query));
        int idot=sendbuf+sizeof(DNS_HEARDER),i=0;
        unsigned char num=0;
        for(i=0;i<=strlen(query);i++){
            if(i==strlen(query) || argv[1][i]=='.'){
                sendbuf[idot]=num;
                idot+=num;
                num=0;
            }else
                num++;
        }
        sendbuf[idot] = num;
        pDNSQueryHDR pqhdr = (pDNSQueryHDR)(sendbuf+idot+1);
        pqhdr->queryType=htons(0x0001);
        pqhdr->queryClass=htons(0x0001);
    }else{              //ip地址查询域名
        pDNSQueryHDR pqhdr = (pDNSQueryHDR)(sendbuf+sizeof(DNS_HEARDER));
        pqhdr->queryName = htonl(inet_addr(query));
        pqhdr->queryType = htons(0x000c);
        pqhdr->queryClass = htons(0x0001);
    }
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  decodeDNSPacket
 *  Description:  
 * =====================================================================================
 */
void decodeDNSPacket(char *recvbuf)
{
    pDNSHDR phdr = (pDNSHDR)recvbuf;
    if(phdr->type==getpid() && (phdr->sig >> 15)){       //说明是本程序需要的dns响应报文
        //判断是否是错误报文
        if(phdr->sig&0x000f == 3){
            printf("名字错误，域名不存在");
            return ;
        }
        //判断是否是授权回答
        if((phdr->sig>>10)==33)
            printf("授权回答\n");
        else
            printf("非授权回答\n");
        int queNum = ntohs(phdr->questionNum);
        int resNum = ntohs(phdr->resNum);
        int authNum = ntohs(phdr->authqueNum);
        int oqueNum = ntohs(phdr->oqusNum);
        char * presponHdr = recvbuf+sizeof(DNS_HEARDER);
        while(*presponHdr++);
        pDNSQueryHDR pquehdr= (pDNSQueryHDR)presponHdr;
        if(ntohs(pquehdr->type)==1){
            printf("address:");
        }else if(ntohs(pquehdr)->type==2){
            printf("names:");
        }
        presponHdr+=sizeof(DNSQueryHDR);
        for(int i=i;i<=resNum;i++){
            if((*(unsigned short *)presponHdr>>14)==3){
                printf("是一个指针");           //是一个域名指针
                presponHdr+=sizeof(unsigned short);
            }else{
                while(*presponHdr++);
            }
            pRESPONCEHDR hreshdr = (pRESPONCEHDR)presponHdr;
            presponHdr+=sizeof(RESPONCEHDR);
            unsigned short dataLen = *(unsigned short *)presponHdr;
            presponHdr+=sizeof(unsigned short);   //数据长度
            if(ntohs(hreshdr->type)==1){   //是一个ip地址
                unsigned long ip = *(unsigned long*)presponHdr;
                printf(" ip =%s ",inet_ntoa(ip));
            }else if(ntohs(hreshdr->type)==5){
                char name[datalen];
                memcpy(name,presponHdr,datalen);
                printf("规范名称:%s\n",name);
            }
            presponHdr+=datalen;
            if(i!=resNUm)
               printf("\n");
        }
    }
}		/* -----  end of function decodednspacket  ----- */
