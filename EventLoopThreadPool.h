/*
 * @Author: zhongxian.chen
 * @Date: 2023-02-19 11:40:17
 * @LastEditors: zhongxian.chen
 * @LastEditTime: 2023-02-19 11:58:18
 * @Description: 
 * 
 * Copyright (c) 2023 by zhongxian.chen, All Rights Reserved. 
 */
#ifndef EVENTLOOPTHREADPOOL_H
#define EVENTLOOPTHREADPOOL_H

#include "EventLoopThread.h"
#include "base/Logging.h"
#include "base/noncopyable.h"
#include <memory>
#include <vector>

class EventLoopThreadPool : noncopyable{
public:
    EventLoopThreadPool(EventLoop* baseloop,int numThreads);
    ~EventLoopThreadPool() { LOG << "~EventLoopThreadPool()"; }
    void start();
    EventLoop* getNextLoop();
private:
    EventLoop* baseLoop_;
    bool started_;
    int numThreads_;
    int next_;
    std::vector<std::shared_ptr<EventLoopThread>> threads_;
    std::vector<EventLoop*> loops_;
};

#endif//