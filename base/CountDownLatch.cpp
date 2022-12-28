
/*
 * @Author: zhongxian.chen
 * @Date: 2022-12-27 21:37:47
 * @LastEditors: zhongxian.chen
 * @LastEditTime: 2022-12-27 22:22:31
 * @Description: 
 * 
 * Copyright (c) 2022 by zhongxian.chen, All Rights Reserved. 
 */
#ifndef BASE_COUNTDOWNLATCH_CPP
#define BASE_COUNTDOWNLATCH_CPP

#include "CountDownLatch.h"

CountDownLatch::CountDownLatch(int count) : mutex_(),cond_(mutex_),count_(count){}

void CountDownLatch::wait(){
    MutexLockGuard lock(mutex_);
    while(count_ > 0) cond_.wait();
}

void CountDownLatch::countDown(){
    MutexLockGuard lock(mutex_);
    --count_;
    if(count_ == 0)
        cond_.notifyAll();
}
int CountDownLatch::getCount() const{
    MutexLockGuard lock(mutex_);
    return count_;
}
#endif
