/*
 * @Author: zhongxian.chen
 * @Date: 2023-02-13 21:53:26
 * @LastEditors: zhongxian.chen
 * @LastEditTime: 2023-02-15 21:44:40
 * @Description: 
 * 
 * Copyright (c) 2023 by zhongxian.chen, All Rights Reserved. 
 */
#ifndef EPOLL_H
#define EPOLL_H

#include <sys/epoll.h>
#include <memory>
#include <unordered_map>
#include <vector>

#include "Channel.h"
#include "HttpData.h"
#include "Timer.h"

class Epoll{
public:
    Epoll();
    ~Epoll();
    void epoll_add(ChannelPtr request,int timeout);
    void epoll_mod(ChannelPtr request,int timeout);
    void epoll_del(ChannelPtr request);
    std::vector<std::shared_ptr<Channel>> poll();
    std::vector<std::shared_ptr<Channel>> getEventRequest(int events_num);
    void add_timer(std::shared_ptr<Channel> request_data,int timeout);
    int getEpollFd(){return epollFd_;}
    void handleExpired();
private:
    static const int MAXFDS = 10000;
    int epollFd_;
    std::vector<epoll_event> events_;
    std::shared_ptr<Channel> fd2chan_[MAXFDS];
    std::shared_ptr<HttpData> fd2http_[MAXFDS];
    TimerManager timerManager_;
};
#endif