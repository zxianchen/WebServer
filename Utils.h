/*
 * @Author: zhongxian.chen
 * @Date: 2023-02-19 16:02:36
 * @LastEditors: zhongxian.chen
 * @LastEditTime: 2023-02-19 16:03:02
 * @Description: 
 * 
 * Copyright (c) 2023 by zhongxian.chen, All Rights Reserved. 
 */
#ifndef UTILS_H
#define UTILS_H
#include <cstdlib>
#include <string>

ssize_t readn(int fd, void *buff, size_t n);
ssize_t readn(int fd, std::string &inBuffer, bool &zero);
ssize_t readn(int fd, std::string &inBuffer);
ssize_t writen(int fd, void *buff, size_t n);
ssize_t writen(int fd, std::string &sbuff);
void handle_for_sigpipe();
int setSocketNonBlocking(int fd);
void setSocketNodelay(int fd);
void setSocketNoLinger(int fd);
void shutDownWR(int fd);
int socket_bind_listen(int port);
#endif