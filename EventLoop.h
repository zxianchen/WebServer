/*
 * @Author: zhongxian.chen
 * @Date: 2023-02-15 22:55:25
 * @LastEditors: zhongxian.chen
 * @LastEditTime: 2023-02-19 16:05:21
 * @Description:
 *
 * Copyright (c) 2023 by zhongxian.chen, All Rights Reserved.
 */
#ifndef EVENTLOOP_H
#define EVENTLOOP_H

#include "base/Thread.h"
#include "base/LogFile.h"
#include "base/CurrentThread.h"
#include "Channel.h"
#include "Epoll.h"
#include "Utils.h"

#include <functional>
#include <memory>
#include <vector>
#include <iostream>
#include <assert.h>
class EventLoop
{
public:
    typedef std::function<void()> Functor;
    EventLoop();
    ~EventLoop();
    void loop();
    void quit();
    void runInLoop(Functor &&cb);
    void queueInLoop(Functor &&cb);
    bool isInLoopThread() const { return threadId_ == CurrentThread::tid(); }
    void assertInLoopThread() { assert(isInLoopThread()); }
    void shutdown(std::shared_ptr<Channel> channel) { shutDownWR(channel->getFd()); }
    void removeFromPoller(std::shared_ptr<Channel> channel)
    {
        // shutDownWR(channel->getFd());
        poller_->epoll_del(channel);
    }
    void updatePoller(std::shared_ptr<Channel> channel, int timeout = 0)
    {
        poller_->epoll_mod(channel, timeout);
    }
    void addToPoller(std::shared_ptr<Channel> channel, int timeout = 0)
    {
        poller_->epoll_add(channel, timeout);
    }

private:
    bool looping_;
    std::shared_ptr<Epoll> poller_;
    int wakeupFd_;
    bool quit_;
    bool eventHandleing_;
    mutable MutexLock mutex_;
    std::vector<Functor> pendingFunctors_;
    bool callingPendingFunctors_;
    const pid_t threadId_;
    std::shared_ptr<Channel> pwakeupChannel_;

    void wakeup();
    void handleRead();
    void doPendingFunctors();
    void handleConn();
};

#endif EVENTLOOP_H