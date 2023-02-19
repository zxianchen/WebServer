/*
 * @Author: zhongxian.chen
 * @Date: 2023-02-19 15:18:10
 * @LastEditors: zhongxian.chen
 * @LastEditTime: 2023-02-19 15:23:49
 * @Description:
 *
 * Copyright (c) 2023 by zhongxian.chen, All Rights Reserved.
 */
#ifndef SERVER_H
#define SERVER_H

#include "Channel.h"
#include "EventLoop.h"
#include "EventLoopThreadPool.h"

class Server
{
public:
    Server(EventLoop *loop, int threadNum, int port);
    ~Server() {}
    EventLoop *getLoop() const { return loop_; }
    void start();
    void handNewConn();
    void handThisConn() { loop_->updatePoller(acceptChannel_); }

private:
    EventLoop *loop_;
    int threadNum_;
    std::unique_ptr<EventLoopThreadPool> eventLoopThreadPool_;
    bool started_;
    std::shared_ptr<Channel> acceptChannel_;
    bool port_;
    int listenFd_;
    static const int MAXFDS = 100000;
};

#endif