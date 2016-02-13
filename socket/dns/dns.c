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
#include    <string.h>
#include    <unistd.h>
#include    <errno.h>
#include    <signal.h>
#include    "dns.h"
#define ERR_EXIT(name) do{          \
        perror(#name);              \
        exit(EXIT_FAILURE);         \
}while(0)


void  sig_handle(int sig){
    printf("recv timeout");
    printf("%d,%s",errno,strerror(errno));
    exit(-1);
}
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
    char sendbuf[MAX_SIZE],recvbuf[MAX_SIZE];
    memset(&seraddr,0,sizeof(seraddr));
    seraddr.sin_family = AF_INET;
    seraddr.sin_port = htons(53);
    seraddr.sin_addr.s_addr = inet_addr("8.8.8.8");
    if((sock = socket(AF_INET,SOCK_DGRAM,0))==-1)
        ERR_EXIT("socket error");
    getDNSHeader(sendbuf);
    getDNSQueryHdr(sendbuf,argv[1]);
    int timeout=3000;
    setsockopt(sock,SOL_SOCKET,SO_SNDTIMEO,(void *)&timeout,sizeof(int));
    setsockopt(sock,SOL_SOCKET,SO_RCVTIMEO,(void *)&timeout,sizeof(int));
    signal(SIGALRM,sig_handle);
    if(sendto(sock,sendbuf,sizeof(sendbuf),0,(struct sockaddr*)&seraddr,sizeof(seraddr))==-1)
        ERR_EXIT("send to error");
    socklen_t len = sizeof(recvaddr);
    int recvlen = 0;
    while(1){
        alarm(3);
        if((recvlen=recvfrom(sock,recvbuf,sizeof(recvbuf),0,(struct sockaddr*)&recvaddr,&len))==-1)
            ERR_EXIT("recv error");
        /*unsigned char * pbuf = (unsigned char *)recvbuf;
        int m =0;
        while(m<recvlen){
            printf("%.2x ",*pbuf);
            pbuf+=sizeof(unsigned char);
            m+=sizeof(unsigned char );
        }*/
        decodeDNSPacket(recvbuf);
        break;
    }
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
    hdr->type=htons(getpid());
    hdr->sig = htons(0x0100);
    hdr->questionNum = htons(0x0001);
    hdr->resNum= htons(0x0000);
    hdr->authqueNum=htons(0x0000);
    hdr->oqusNum=htons(0x0000);
}		/* -----  end of function getDNSHeader  ----- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  getDNSQueryHdr
 *  Description:  封装头部查询
 * =====================================================================================
 */
void getDNSQueryHdr (char *sendbuf,char *query)
{
    if(inet_addr(query)==INADDR_NONE){                //说明不是一个点分十进制的ip地址，而是一个是域名
        memcpy(sendbuf+sizeof(DNS_HEARDER)+1,query,strlen(query));
        char * idot=sendbuf+sizeof(DNS_HEARDER);
        int i=0;
        unsigned char num=0;
        for(i=0;i<=strlen(query);i++){
            if(i==strlen(query) || query[i]=='.'){
                *idot=num;
                idot+=num+1;
                num=0;
            }else
                num++;
        }
        *idot = num;
        pDNSQueryHDR pqhdr = (pDNSQueryHDR)(idot+1);
        pqhdr->queryType=htons(0x0001);
        pqhdr->queryClass=htons(0x0001);
    }else{              //ip地址查询域名
        int i=strlen(query)-1,j=0;
        int m =i+1,n=0;
        char * temp = (char *)malloc(strlen(query)+1);
        for(;i>=-1;i--){
            if(i==-1 || query[i] == '.'){
                for(n=i+1;n<m;n++){
                    temp[j++] = query[n];
                }
                m=i;
                temp[j++]='.';
            }
        }
        strcat(temp,"in-addr.arpa");
        memcpy(sendbuf+sizeof(DNS_HEARDER)+1,temp,strlen(temp));
        char * idot=sendbuf+sizeof(DNS_HEARDER);
        unsigned char num=0;
        for(i=0;i<=strlen(temp);i++){
            if(i==strlen(temp) || temp[i]=='.'){
                *idot=num;
                idot+=num+1;
                num=0;
            }else
                num++;
        }
        *idot = num;
        // memcpy(sendbuf+sizeof(DNS_HEARDER),temp,strlen(temp));
        //pDNSQueryHDR pqhdr = (pDNSQueryHDR)(sendbuf+sizeof(DNS_HEARDER)+strlen(temp));
        pDNSQueryHDR pqhdr = (pDNSQueryHDR)(idot+1);
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
    if(ntohs(phdr->type)==getpid() && (phdr->sig >> 15)){       //说明是本程序需要的dns响应报文
        //判断是否是错误报文
        if((ntohs(phdr->sig)&0x000f) == 3){
            printf("名字错误，域名不存在");
            return ;
        }
        //判断是否是授权回答
        if((ntohs(phdr->sig)>>10)==33)
            printf("授权回答\n");
        else
            printf("非授权回答\n");
        int queNum = ntohs(phdr->questionNum);
        int resNum = ntohs(phdr->resNum);
        int authNum = ntohs(phdr->authqueNum);
        int oqueNum = ntohs(phdr->oqusNum);
        printf("问题数：%d,结果数 %d,授权回答 %d,其它回答：%d\n",queNum,resNum,authNum,oqueNum);
        char * presponHdr = recvbuf+sizeof(DNS_HEARDER);
        while(*presponHdr){
            presponHdr++;
        }
        presponHdr++;
        pDNSQueryHDR pquehdr= (pDNSQueryHDR)presponHdr;
        if(ntohs(pquehdr->queryType)==1){
            printf("address:\n");
        }else if(ntohs(pquehdr->queryType)==12){
            printf("names:\n");
        }
        presponHdr+=sizeof(DNSQueryHDR);
        int i;
        for(i=0;i<resNum;i++){
            if((ntohs(*(unsigned short *)presponHdr)>>14)==3){
                presponHdr+=sizeof(unsigned short);
            }else{
                while(*presponHdr){
                    presponHdr++;
                }
                presponHdr++;
            }
            pRESPONCEHDR hreshdr = (pRESPONCEHDR)presponHdr;
            presponHdr+=sizeof(RESPONCEHDR);
            unsigned short dataLen = ntohs(*(unsigned short *)presponHdr);
            presponHdr+=sizeof(unsigned short);   //数据长度
            if(ntohs(hreshdr->type)==1){   //是一个ip地址,
                struct  in_addr ip;
                memset(&ip,0,sizeof(struct in_addr));
                ip.s_addr = *(unsigned int*)presponHdr;
                printf(" ip =%s ",inet_ntoa(ip));
            }else if(ntohs(hreshdr->type)==5){
                char name[dataLen];
                memcpy(name,presponHdr,dataLen);
                int m=0,k;
                while(m<strlen(name)){
                    k=m;
                    m+=name[m]+1;
                    name[k] = '.';
                }
                name[k]='\0';
                printf("规范名称:%s",name+1);
            }else if(ntohs(hreshdr->type)==12){
                char name[dataLen];
                memcpy(name,presponHdr,dataLen);
                int m=0,k;
                while(m<strlen(name)){
                    k=m;
                    m+=name[m]+1;
                    name[k] = '.';
                }
                name[k] = '\0';
                printf("域名:%s\n",name+1);
            }
            presponHdr+=dataLen;
            if(i!=resNum)
               printf("\n");
        }
    }else{
        printf("%s","包错误");
    }
}		/* -----  end of function decodednspacket  ----- */
