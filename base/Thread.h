/*
 * @Author: zhongxian.chen
 * @Date: 2022-12-28 20:01:09
 * @LastEditors: zhongxian.chen
 * @LastEditTime: 2022-12-28 21:04:47
 * @Description: 
 * 
 * Copyright (c) 2022 by zhongxian.chen, All Rights Reserved. 
 */
#ifndef BASE_THREAD_H
#define BASE_THREAD_H

#include "noncopyable.h"
#include "CountDownLatch.h"

#include <functional>
#include <pthread.h>
#include <string>
#include <sys/types.h>

class Thread : noncopyable{
public:
    typedef std::function<void()> ThreadFunc;
    explicit Thread(const ThreadFunc&,const std::string& name = std::string());
    ~Thread();
    void start();
    int join();
    bool started() const { return started_; }
    pid_t tid() const { return tid_; }
    const std::string& name() const { return name_; }
private:
    void setDefaultName();
    bool started_;
    bool joined_;
    pthread_t pthreadId_;
    pid_t tid_;
    ThreadFunc func_;
    std::string name_;
    CountDownLatch latch_;
};

#endif