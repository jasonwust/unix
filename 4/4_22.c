/*
 * =====================================================================================
 *       Filename:  4_22.c
 *    Description:  遍历目录结构,获取各种文件类型的计数
 *        Version:  1.0
 *        Created:  2015年06月03日 20时44分35秒
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 * =====================================================================================
 */

#include	<stdlib.h>
#include    <stdio.h>
#include <error.h>
#include <dirent.h>
#include <limits.h>
#include <sys/stat.h>
#include <string.h>
#define ERR_EXIT(name)        \
    do{                         \
        perror(#name);          \
        exit(EXIT_FAILURE);     \
    }while(0)

typedef int Myfunc(const char *,const struct stat *,int);
static Myfunc myfunc;
static int myftw(char *,Myfunc *);
static int dopath(Myfunc *);
static long nreg,ndir,nblk,nchr,nfifo,nslink,nsock,ntot;

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
int main ( int argc, char *argv[] )
{
    int ret;
    if(argc!=2)
        ERR_EXIT("参数个数不对");
    ret = myftw(argv[1],myfunc);
    ntot = nreg + ndir + nblk + nchr + nfifo + nslink + nsock;
    if(ntot==0)
        ntot =1;
    printf("regular files = %7ld, %5.2f %%\n",nreg,nreg*100.0/ntot);
    printf("directories   = %7ld, %5.2f %%\n",ndir,ndir*100.0/ntot);
    printf("block special = %7ld, %5.2f %%\n",nblk,nblk*100.0/ntot);
    printf("char special  = %7ld, %5.2f %%\n",nchr,nchr*100.0/ntot);
    printf("fifos         = %7ld, %5.2f %%\n",nfifo,nfifo*100.0/ntot);
    printf("symbolic links = %7ld, %5.2f %%\n",nslink,nslink*100.0/ntot);
    printf("sockets       = %7ld, %5.2f %%\n",nsock,nsock*100.0/ntot);
    return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */

#define FTW_F 1
#define FTW_D 2
#define FTW_DNR 3
#define FTW_NS 4

static char *fullpath;
static size_t pathlen;
/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  myftw
 *  Description:  
 * =====================================================================================
 */
static int myftw(char *pathname,Myfunc *func){
    fullpath = malloc(sizeof(char)*pathlen);
    if(pathlen <= strlen(pathname)){
        pathlen = strlen(pathname) * 2;
        if((fullpath = realloc(fullpath,pathlen))==NULL)
            ERR_EXIT("relloc failed");
    }
    strcpy(fullpath,pathname);
    return(dopath(func));
}
/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  dopath
 *  Description:  
 * =====================================================================================
 */
static int dopath(Myfunc *func){
    struct stat statbuf;
    struct dirent *dirp;
    DIR * dp;
    int ret,n;
    if(lstat(fullpath,&statpath)<0)
        return(func(fullpath,&statbuf,FTW_NS));
    if(S_ISDIR(statbuf.st_mode) == 0)
        return(func(fullpath,&statbuf,FTW_F));
    if((ret = func(fullpath,&statbuf,FTW_D))!=0)
        return(ret);
}

