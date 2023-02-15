/*
 * @Author: zhongxian.chen
 * @Date: 2023-02-12 12:49:07
 * @LastEditors: zhongxian.chen
 * @LastEditTime: 2023-02-13 20:54:53
 * @Description:
 *
 * Copyright (c) 2023 by zhongxian.chen, All Rights Reserved.
 */
#include "Time.h"

#include <sys/time.h>
#include <unistd.h>
#include <queue>

TimerNode::TimerNode(std::shared_ptr<HttpData> requestData, int timeout)
    : deleted_(false), HttpData_(requestData)
{
    struct timeval now;
    gettimeofday(&now, NULL);
    // 以毫秒计
    expiredTime_ =
        (((now.tv_sec % 10000) * 1000) + (now.tv_usec / 1000)) + timeout;
}

TimerNode::~TimerNode()
{
    if (HttpData_)
        HttpData_->handleClose();
}

TimerNode::TimerNode(TimerNode &tn)
    : HttpData_(tn.HttpData_), expiredTime_(0) {}

void TimerNode::update(int timeout)
{
    struct timeval now;
    gettimeofday(&now, NULL);
    expiredTime_ =
        (((now.tv_sec % 10000) * 1000) + (now.tv_usec / 1000)) + timeout;
}

bool TimerNode::isValid()
{
    struct timeval now;
    gettimeofday(&now, NULL);
    size_t temp = (((now.tv_sec % 10000) * 1000) + (now.tv_usec / 1000));
    if (temp < expiredTime_)
        return true;
    else
    {
        this->setDeleted();
        return false;
    }
}

void TimerNode::clearReq(){
    HttpData_.reset();
    this->setDeleted();
}

TimerManager::TimerManager() {}
TimerManager::~TimerManager() {}

void TimerManager::addTimer(std::shared_ptr<HttpData> httpdata,int timeout){
    TimerNodePtr new_node(new TimerNode(httpdata,timeout));
    timerNodeQueue_.push(new_node);
    httpdata->linkTimer(new_node);
}

void TimerManager::handleExpiredEvent(){
    while(!timerNodeQueue_.empty()){
        TimerNodePtr ptimer = timerNodeQueue_.top();
        if(ptimer->isDeleted())
            timerNodeQueue_.pop();
        else if(ptimer->isValid() == false)
            timerNodeQueue_.pop();
        else
            break;
    }
}