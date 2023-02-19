/*
 * @Author: zhongxian.chen
 * @Date: 2022-12-27 21:30:11
 * @LastEditors: zhongxian.chen
 * @LastEditTime: 2023-02-19 16:00:05
 * @Description: 
 * 
 * Copyright (c) 2022 by zhongxian.chen, All Rights Reserved. 
 */
#ifndef BASE_COUNTDOWNLATCH_H
#define BASE_COUNTDOWNLATCH_H

#include "noncopyable.h"
#include "MutexLock.h"
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