/*
 * =====================================================================================
 *       Filename:  ping.c
 *    Description:  简单的ping程序实现
 *        Version:  1.0
 *        Created:  2015年09月17日 14时00分13秒
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 * =====================================================================================
 */


#include	<stdlib.h>
#include    <stdio.h>
#include <netdb.h>    //getprotobynumber gethostname
#include <unistd.h>     //setuid getuid sleep alarm
#include <sys/types.h>
#include <signal.h>
#include <sys/time.h>
#include <netinet/ip_icmp.h>
#include <string.h>
#include <errno.h>          //EINTR
#include <arpa/inet.h>     //inet_ntoa()
#define MAX_NO_PACKETS 10
#define PACKET_SIZE 4096
#define MAX_WAIT_TIME 5
/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
int sockfd;
int datalen = 56;
struct sockaddr_in dest_addr;
struct sockaddr_in from;

pid_t pid;
int nsend =0;
int nreceive = 0;
char sendpacket[PACKET_SIZE];
char recvpacket[PACKET_SIZE];
struct timeval tvrecv;
void statistics();      /*显示主体信息*/
void send_packet();    //发送icmp
void recv_packet();    //接受所有icmp包
int main ( int argc, char *argv[] )
{
    struct protoent *protocol;
    int size = 1024*50;
    unsigned int inaddr = 0l; //0L
    struct hostent*host;
    if(argc<2){
        printf("usage:%s hostname/IP address:%s hostname/IP address- \r\r\n",argv[0],argv[0]);
        exit(1);
    }
    if((protocol=getprotobyname("icmp"))==NULL){
        perror("getprotobyname error");
        exit(1);
    }
    if((sockfd=socket(AF_INET,SOCK_RAW,protocol->p_proto)) <0){
        perror("socket error");
        exit(1);
    }
    //设置接受缓存大小
    setsockopt(sockfd,SOL_SOCKET,SO_RCVBUF,&size,sizeof(size));
    bzero(&dest_addr,sizeof(dest_addr));
    dest_addr.sin_family = AF_INET;
    inaddr = inet_addr(argv[1]);
    //判断用户传入的是主机名，还是ip地址
    if(inaddr == INADDR_ANY){
        if((host = gethostbyname(argv[1]))==NULL){
            perror("gethostbyname error");
            exit(1);
        }
        memcpy((char *)&dest_addr.sin_addr,host->h_addr,sizeof(dest_addr.sin_addr));
    }else
        memcpy((char *)&dest_addr.sin_addr,(char *)&inaddr,sizeof(inaddr));
     pid = getpid();
     printf("PING %s(%s):%d bytes data in ICMP packets\n",argv[1],inet_ntoa(dest_addr.sin_addr),datalen);
     //接受终端信号，即ctrl+c产生的信号
     signal(SIGINT,statistics);
     if(argc==2){
        send_packet();
        //recv_packet();
        statistics();
    }
    return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
unsigned short cal_chksum(unsigned short *addr,int len){
    int nleft = len;
    int sum =0;
    unsigned short *w =addr;
    unsigned short answer=0;
    while(nleft >1){
        sum+=*w++;
        nleft-=2;
    }
    if(nleft ==1){
        *(unsigned char *)(&answer)= *(unsigned char*)w;
        sum+=answer;
    }
    sum = (sum>>16)+(sum&0xffff);
    sum+=(sum>>16);
    answer=~sum;
    return answer;
}

//计算时间
void tv_sub(struct timeval*out,struct timeval *in){
    if((out->tv_usec-=in->tv_usec)<0){
        --out->tv_sec;
        out->tv_sec+=1000000;
    }
    out->tv_sec-=in->tv_sec;
}

//icmp header
int pack_header(int pack_no){
    int packsize;
    struct icmp*icmp;
    struct timeval *tval;
    icmp = (struct icmp *)sendpacket;
    icmp->icmp_type = ICMP_ECHO;
    icmp->icmp_code = 0;
    icmp->icmp_cksum =0;
    icmp->icmp_seq = pack_no;
    icmp->icmp_id = pid;
    packsize = datalen+8;
    tval = (struct timeval *)icmp->icmp_data;
    gettimeofday(tval,NULL);
    icmp->icmp_cksum = cal_chksum((unsigned short *)icmp,packsize);
    return packsize;

}
//剥去头部
int unpack_header(char *buf,int len){
    int iphdrlen;
    struct ip *ip;
    struct icmp *icmp;
    struct timeval *tvsend;
    double rtt;
    ip = (struct ip *)buf;
    iphdrlen = ip->ip_hl<<2;
    icmp = (struct icmp*)(buf+iphdrlen);
    len -=  iphdrlen;
    if(len<8){
        printf("ICMP　packet\'s length is less than 8\n");
        return -1;
    }
    if((icmp->icmp_type==ICMP_ECHOREPLY)&&(icmp->icmp_id==pid)){
        tvsend = (struct timeval *)icmp->icmp_data;
        tv_sub(&tvrecv,tvsend);
        rtt = tvrecv.tv_sec*1000 + tvrecv.tv_usec/1000;
        printf("%d byte from %s:icmp_seq=%u ttl=%d rtt=%.3f ms\n",len,inet_ntoa(from.sin_addr),icmp->icmp_seq,ip->ip_ttl,rtt);
        return 0;
    }
    return -1;
}


void statistics(){
    printf("\n------------------ping statisticcs--------------\n");
    printf("%d packets transmitted,%d receive,%.2f%% packets lost\n",nsend,nreceive,(float)(nsend-nreceive)/nsend*100);
    printf("\n-------------------------------------------------\n");
    close(sockfd);
}

void send_packet(){
    int packsize ;
    while(nsend<MAX_NO_PACKETS){
        nsend++;
        packsize = pack_header(nsend);
        if(sendto(sockfd,sendpacket,packsize,0,(struct sockaddr*)&dest_addr,sizeof(dest_addr))<0){
            perror("sendto error");
            continue;
        }
        recv_packet();
        sleep(1);
    }
}
void recv_packet(){
    int n,fromlen;
    extern int errno;
    signal(SIGALRM,statistics);
    fromlen = sizeof(from);
    while(nreceive <nsend){
        alarm(MAX_WAIT_TIME);
        if((n=recvfrom(sockfd,recvpacket,sizeof(recvpacket),0,(struct sockaddr *)&from,&fromlen))<0){
            if(errno==EINTR)
                continue;
            perror(" reveive error");
            continue;
        }
        gettimeofday(&tvrecv,NULL);
        if(unpack_header(recvpacket,n)==-1)
            continue;
        nreceive++;
    }
}
