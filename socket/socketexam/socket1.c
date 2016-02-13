/*
 * =====================================================================================
 *       Filename:  socket1.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2015年10月16日 11时01分43秒
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 * =====================================================================================
 */

#include	<stdlib.h>
#include    <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
int main ( int argc, char *argv[] )
{
    struct hostent * host ;
    while((host =  gethostent())!=NULL){
        char ** aliases=NULL;
        char **addr_list = NULL;
        char addr_p[INET_ADDRSTRLEN];   // IPV4
        printf("hostname: %s\n", host->h_name);
        for(aliases = host->h_aliases; *aliases; aliases++)
        {
            printf("alternate name: %s\n", *aliases);
        }
        /*  print address type and length */
        if(host->h_addrtype == AF_INET)  
        {
            printf("address type: AF_INET\n");
        }
        else
       {
            printf("Not an IPv4 address.\n");
       }
       printf("address length: %d\n", host->h_length);
      /*  print address list */
      //printf("%d\n", sizeof(*(host->h_addr_list)));
       printf("%x\n", *(int *)(*(host->h_addr_list)));
      for(addr_list = host->h_addr_list; *addr_list; addr_list++)  
      {
        printf("address: %s\n", inet_ntop(host->h_addrtype, *addr_list, addr_p, INET_ADDRSTRLEN));
      }
    }
    return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */

