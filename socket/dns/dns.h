/*
 * =====================================================================================
 *       Filename:  dns.h
 *    Description: dns 报文头文件
 *        Version:  1.0
 *        Created:  2015年11月21日 13时33分41秒
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 * =====================================================================================
 */
#ifndef DNS_H
#define DNS_H
#define MAX_SIZE 1024
typedef struct{
    unsigned short type;
    unsigned short sig;
    unsigned short questionNum;
    unsigned short resNum;
    unsigned short authqueNum;
    unsigned short oqusNum;
}DNS_HEARDER,* pDNSHDR;
typedef struct {
    unsigned short queryType;
    unsigned short queryClass;
}DNSQueryHDR,* pDNSQueryHDR;
typedef struct{
    unsigned short type;
    unsigned short className;
    unsigned int ttl;
}RESPONCEHDR,*pRESPONCEHDR;
void getDNSHeader(char * buf);
void getDNSQueryHdr(char *buf,char *query);
void decodeDNSPacket(char *buf);

#endif
