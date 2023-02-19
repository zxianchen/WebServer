/*
 * @Author: zhongxian.chen
 * @Date: 2023-02-19 11:26:44
 * @LastEditors: zhongxian.chen
 * @LastEditTime: 2023-02-19 16:06:30
 * @Description:
 *
 * Copyright (c) 2023 by zhongxian.chen, All Rights Reserved.
 */
#ifndef EVENTLOOPTHREAD_H
#define EVENTLOOPTHREAD_H

#include "EventLoop.h"
#include "base/Condition.h"
#include "base/MutexLock.h"
#include "base/Thread.h"
#include "base/noncopyable.h"

class EventLoopThread : noncopyable
{
public:
    EventLoopThread();
    ~EventLoopThread();
    EventLoop *startLoop();
private:
    void threadFunc();
    EventLoop* loop_;
    bool exiting_;
    Thread thread_;
    MutexLock mutex_;
    Condition cond_;
};
#endif