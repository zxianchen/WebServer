/*
 * @Author: zhongxian.chen
 * @Date: 2022-12-27 21:30:11
 * @LastEditors: zhongxian.chen
 * @LastEditTime: 2022-12-27 21:33:32
 * @Description: 
 * 
 * Copyright (c) 2022 by zhongxian.chen, All Rights Reserved. 
 */
#ifndef BASE_COUNTDOWNLATCH_H
#define BASE_COUNTDOWNLATCH_H

#include "noncopyable.h"
#include "Mutex.h"
#include "Condition.h"

class CountDownLatch : noncopyable{
public:
    explicit CountDownLatch(int count);
    void wait();
    void countDown();
    int getCount() const;
private:
    mutable MutexLock mutex_;
    Condition cond_;
    int count_;
};
#endif