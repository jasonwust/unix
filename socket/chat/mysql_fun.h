/*
 * =====================================================================================
 *       Filename:  myslq_fun.h
 *    Description:  mysql数据库操作函数封装库
 *        Version:  1.0
 *        Created:  2015年11月03日 19时56分20秒
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 * =====================================================================================
 */
#ifndef MYSQL_FUN_H
#define MYSQL_FUN_H
#include <mysql.h>
//连接mysql
typedef struct{
    char *host;
    char * username;
    char * password;
    short port;
    char * database;
    char * charset;
}MYSQLINFO;
bool mysql_conn(MYSQLINFO *info,MYSQL *mysql);

endif
