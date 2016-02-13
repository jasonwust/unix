/*
 * =====================================================================================
 *       Filename:  chat.h
 *    Description:  聊天客户端
 *        Version:  1.0
 *        Created:  2015年11月03日 19时00分41秒
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 * =====================================================================================
 */
#ifndef CHAT_H
#define CHAT_H

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <error.h>
#include <string.h>
#include <stdio.h>
#include "function.h"
MYSQL mysql;
typedef struct {
    username[20];
    bool islogin;
}FRIEND,*FRIENDS;
void getFriends();
void addFriends();
void createRoom();
void closeRoom();




#endif
