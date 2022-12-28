/*
 * @Author: zhongxian.chen
 * @Date: 2022-12-27 20:35:51
 * @LastEditors: zhongxian.chen
 * @LastEditTime: 2022-12-27 21:12:45
 * @Description: 
 * 
 * Copyright (c) 2022 by zhongxian.chen chenzhongxian06@gmail.com, All Rights Reserved. 
 */
#ifndef BASE_MUTEX_H
#define BASE_MUTEX_H

#include "noncopyable.h"

#include <pthread.h>

class MutexLock : noncopyable{
public:
    MutexLock(){
        pthread_mutex_init(&mutex_,NULL);        
    }
    ~MutexLock() {
        pthread_mutex_destroy(&mutex_);
    }
    void lock(){
        pthread_mutex_lock(&mutex_);
    }
    void unlock(){
        pthread_mutex_unlock(&mutex_);
    }
    pthread_mutex_t* get(){
        return &mutex_;
    }

private:
    pthread_mutex_t mutex_;
    friend class Condition;
};

class MutexLockGuard : noncopyable {
public:
    explicit MutexLockGuard(MutexLock& mutex) : mutex_(mutex){
        mutex_.lock();
    }
    ~MutexLockGuard(){
        mutex_.unlock();
    }
private:
    MutexLock& mutex_;
};


#endif