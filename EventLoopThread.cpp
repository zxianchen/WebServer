/*
 * @Author: zhongxian.chen
 * @Date: 2023-02-19 11:27:07
 * @LastEditors: zhongxian.chen
 * @LastEditTime: 2023-02-19 11:38:48
 * @Description: 
 * 
 * Copyright (c) 2023 by zhongxian.chen, All Rights Reserved. 
 */
#include "EventLoopThread.h"
#include <functional>

EventLoopThread::EventLoopThread()
    :loop_(NULL),
    exiting_(false),
    thread_(std::bind(&EventLoopThread::threadFunc,this),"EventLoopThread"),
    mutex_(),
    cond_(mutex_){

    }

EventLoopThread::~EventLoopThread() {
  exiting_ = true;
  if (loop_ != NULL) {
    loop_->quit();
    thread_.join();
  }
}

EventLoop* EventLoopThread::startLoop(){
    assert(!thread_.started());
    thread_.start();
    {
        MutexLockGuard lock(mutex_);
        while(loop_ == NULL)cond_.wait();
    }
    return loop_;
}

void EventLoopThread::threadFunc(){
    EventLoop loop;
    {
        MutexLockGuard lock(mutex_);
        loop_ = &loop;
        cond_.notify();
    }
    loop.loop();
    loop_ = NULL;
}