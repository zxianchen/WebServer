/*
 * @Author: zhongxian.chen
 * @Date: 2023-02-12 12:48:58
 * @LastEditors: zhongxian.chen
 * @LastEditTime: 2023-02-15 21:44:10
 * @Description:
 *
 * Copyright (c) 2023 by zhongxian.chen, All Rights Reserved.
 */
#ifndef TIMER_H
#define TIMER_H

#include <unistd.h>
#include <deque>
#include <memory>
#include <queue>
#include "HttpData.h"
#include "base/noncopyable.h"
#include "base/Mutex.h"

class HttpData;

class TimerNode
{
public:
   TimerNode(std::shared_ptr<HttpData> requestData, int timeout);
    ~TimerNode();
    TimerNode(TimerNode &tn);
    void update(int timeout);
    bool isValid();
    void clearReq();
    void setDeleted() { deleted_ = true; }
    bool isDeleted() { return deleted_; }
    size_t getExpTime() const { return expiredTime_; }

private:
    bool deleted_;
    size_t expiredTime_;
    std::shared_ptr<HttpData> HttpData_;
};

struct TimerCmp
{
    bool operator()(std::shared_ptr<TimerNode> &a,
                    std::shared_ptr<TimerNode> &b) const
    {
        return a->getExpTime() > b->getExpTime();
    }
};

class TimerManager
{
public:
    TimerManager();
    ~TimerManager();
    void addTimer(std::shared_ptr<HttpData> HttpDataPtr,int timeout);
    void handleExpiredEvent();
private:
    typedef std::shared_ptr<TimerNode> TimerNodePtr;
    std::priority_queue<TimerNodePtr, std::deque<TimerNodePtr>, TimerCmp> timerNodeQueue_;
};

#endif