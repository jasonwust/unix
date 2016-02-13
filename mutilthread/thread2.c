/*
 * =====================================================================================
 *       Filename:  thread2.c
 *    Description:  使用互斥量的线程程序
 *        Version:  1.0
 *        Created:  2015年09月17日 23时43分22秒
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 * =====================================================================================
 */

#include	<stdlib.h>
#include    <stdio.h>
#include    <pthread.h>
/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
struct foo{
    int f_count;
    pthread_nmutex_t f_lock;
    int f_id;
};
struct foo * foo_alloc(int id){
    struct foo* fp;
    if((fp=malloc(sizeof(struct foo)))!=NULL){
        fp->f_count = 1;
        fp->f_id = id;
        if(pthread_mutex_init(&fp->f_lock,NULL)!=0){
            free(fp);
            return NULL;
        }
    }
    return fp;
}

void foo_hold(dtruct foo *fp){
    pthread_mutex_lock(&fp->f_lock);
    fp->f_count++;
    pthread_mutex_unlock(&fp->f_lock);
}
void foo_rele(struct foo*fp){
    pthread_mutex_unlock(&fp->f_lock);
    if(--fp->f_count==0){
        pthread_mutex_unlock(&fp->f_lock);
        pthread_mutex_destroy(&fp->f_lock);
        free(fp);
    }else{
        pthread_mutex_unlock(&fp->f_lock);
    }
}
int main ( int argc, char *argv[] )
{
    
    return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */

