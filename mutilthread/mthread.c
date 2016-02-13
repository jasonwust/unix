/*
 * =====================================================================================
 *       Filename:  mthread.c
 *    Description:  linux多线程实例,本程序的结果具有不确定行，取决于线程执行顺序，由于未加互斥锁，g_flag变量的值也具有不确定性
 *        Version:  1.0
 *        Created:  2015年09月17日 12时38分30秒
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 * =====================================================================================
 */

#include	<stdlib.h>
#include    <stdio.h>
#include <pthread.h>
#include <error.h>
#include <unistd.h>
#include <string.h>
/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */

int g_Flag =0;
void * thread1(void *);
void * thread2(void *);
int main ( int argc, char *argv[] )
{
    printf("enter main");
    pthread_t tid1,tid2;
    int rc1=0,rc2=0;
    //第一个参数是线程id,第二个参数是线程属性，第三个是线程要执行的函数，第四个是传入该函数的参数
    rc2 = pthread_create(&tid2,NULL,thread2,NULL);
    if(rc2 !=0){
        //创建线程出错
        printf("%s:%d\n",__func__,rc2);
        exit(EXIT_FAILURE);
    }
    rc1 = pthread_create(&tid1,NULL,thread1,&tid2);
    if(rc1 !=0){
        //创建线程出错
        printf("%s:%d\n",__func__,rc1);
        exit(EXIT_FAILURE);
    }
    sleep(5);
    printf("leave main\n");
    return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  thread1
 *  Description:  线程1
 * =====================================================================================
 */
void * thread1 (void *args)
{
    printf("enter pthread1");
    printf("this is thread1.g_Flag；%d,thread id is %u\n",g_Flag,(unsigned int)pthread_self());
    g_Flag =1;
    printf("this is thread1.g_Flag；%d,thread id is %u\n",g_Flag,(unsigned int)pthread_self());
    printf("leave thredd1");
    pthread_exit(0);
    return 0;
}		/* -----  end of function thread1  ----- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  thread2
 *  Description:  
 * =====================================================================================
 */

void *thread2 (void *arg )
{
    printf("enter pthread2");
    printf("this is thread2.g_Flag；%d,thread id is %u\n",g_Flag,(unsigned int)pthread_self());
    g_Flag =2;
    printf("this is thread2.g_Flag；%d,thread id is %u\n",g_Flag,(unsigned int)pthread_self());
    printf("leave thredd2");
    pthread_exit(0);
    return 0;
}		/* -----  end of function thread2  ----- */
