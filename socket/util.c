/*
 * =====================================================================================
 *       Filename:  util.c
 *    Description:  util.h 的实现函数
 *        Version:  1.0
 *        Created:  2015年09月16日 16时58分15秒
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 * =====================================================================================
 */
#include "util.h"

ssize_t readn(int fd,void *pstr,size_t n){
    size_t nleft;
    ssize_t nread;
    char *vpstr;
    vpstr = pstr;
    nleft = n;
    while(nleft >0){
        if((nread = read(fd,vpstr,nleft))<0){
            //由于read是慢系统调用，在调用过程中可能终端产生EINTR错误，此时应该继续调用read函数
            if(errno == EINTR){
                nread =0;
            }else
                return -1;
        }else if(nread==0){
            break;
        }
        nleft -=nread;
        vpstr+=nread;
    }
    return n-nleft;
}

ssize_t writen(int fd,const void *pstr,size_t n){
    size_t nleft;
    ssize_t nwritten;
    const char * vpstr;
    vpstr = pstr;
    nleft = n;
    while(nleft>0){
        if((nwritten=write(fd,vpstr,nleft))<=0){
            if(nwritten <0 && errno == EINTR)
                nwritten =0;
            else
                return -1;
        }
        nleft -= nwritten;
       vpstr+=nwritten; 
    }
    return n;
}

ssize_t readLine(int fd,void *pstr,size_t maxlen){
    ssize_t n,rc;
    char c,*vpstr;
    vpstr = pstr;
    for(n=1;n<maxlen;n++){
    again:
        if((rc=read(fd,&c,1))==1){
            *vpstr++ = c;
            if(c=='\n'){
                break;
            }
        }else if(rc ==0){
            *vpstr = 0;
            return n-1;
        }else{
            if(errno==EINTR){
                goto again;
            }
            return -1;
        }
    }
    *vpstr = 0;
    return n;
}

