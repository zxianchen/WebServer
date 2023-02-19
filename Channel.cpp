/*
 * @Author: zhongxian.chen
 * @Date: 2023-02-12 12:44:30
 * @LastEditors: zhongxian.chen
 * @LastEditTime: 2023-02-19 16:16:36
 * @Description:
 *
 * Copyright (c) 2023 by zhongxian.chen, All Rights Reserved.
 */
#include "Channel.h"
#include "Epoll.h"
#include "EventLoop.h"
#include "Utils.cpp"

#include <unistd.h>
#include <cstdlib>
#include <iostream>
#include <queue>

using namespace std;
Channel::Channel(EventLoop *loop)
    : loop_(loop), events_(0), lastEvents_(0), fd_(0) {}

Channel::Channel(EventLoop *loop, int fd)
    : loop_(loop), fd_(fd), events_(0), lastEvents_(0) {}

Channel::~Channel()
{
    // loop_->poller_->epoll_del(fd, events_);
    // close(fd_);
}
int Channel::getFd() { return fd_; }
void Channel::setFd(int fd) { fd_ = fd; }

void Channel::handleRead()
{
    if (readHandler_)
    {
        readHandler_();
    }
}

void Channel::handleWrite()
{
    if (writeHandler_)
    {
        writeHandler_();
    }
}

void Channel::handleConn()
{
    if (connHandler_)
    {
        connHandler_();
    }
}