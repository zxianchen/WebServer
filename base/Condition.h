/*
 * @Author: zhongxian.chen
 * @Date: 2022-12-27 20:44:08
 * @LastEditors: zhongxian.chen
 * @LastEditTime: 2023-02-07 23:31:03
 * @Description: 
 * 
 * Copyright (c) 2022 by zhongxian.chen chenzhongxian06@gmail.com, All Rights Reserved. 
 */
#ifndef BASE_CONDITION_H
#define BASE_CONDITION_H

#include "noncopyable.h"
#include "Mutex.h"

#include <pthread.h>

class Condition : noncopyable{
public:
    explicit Condition(MutexLock& mutex) : mutex_(mutex){
        pthread_cond_init(&pcond_,NULL);
    }
    ~Condition(){
        pthread_cond_destroy(&pcond_);
    }
    void wait(){
        pthread_cond_wait(&pcond_,mutex_.get());
    }
    void notify(){
        pthread_cond_signal(&pcond_);
    }
    void notifyAll(){
        pthread_cond_broadcast(&pcond_);
    }
    bool waitForSeconds(int seconds) {
    struct timespec abstime;
    clock_gettime(CLOCK_REALTIME, &abstime);
    abstime.tv_sec += static_cast<time_t>(seconds);
    return ETIMEDOUT == pthread_cond_timedwait(&pcond_, mutex_.get(), &abstime);
  }
private:
    MutexLock& mutex_;
    pthread_cond_t pcond_;
};


#endif
