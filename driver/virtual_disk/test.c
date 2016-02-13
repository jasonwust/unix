/*
 * =====================================================================================
 *       Filename:  test.c
 *    Description:  test the device
 *        Version:  1.0
 *        Created:  2016年02月07日 18时00分50秒
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 * =====================================================================================
 */

#include	<stdlib.h>
#include    <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
int main ( int argc, char *argv[] )
{
    int fop = open("/dev/virtual_disk",O_RDWR);
    if(fop==-1)
    {
        printf("open dev failed:%s",strerror(errno));
        return -1;
    }
    char buffer[256] = "hello world";
    write(fop,buffer,strlen(buffer));
    memset(buffer,0,sizeof(buffer));
    size_t ret = read(fop,buffer,11);
    buffer[ret] = 0;
    printf("%s\n",buffer);
    return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
