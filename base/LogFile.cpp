/*
 * @Author: zhongxian.chen
 * @Date: 2023-02-05 18:45:01
 * @LastEditors: zhongxian.chen
 * @LastEditTime: 2023-02-05 19:17:04
 * @Description: 
 * 
 * Copyright (c) 2023 by zhongxian.chen, All Rights Reserved. 
 */
#include "LogFile.h"

#include <assert.h>
#include <stdio.h>  
#include <time.h>

using  namespace std;

LogFile::LogFile(const string& basename,int flushEveryN) 
    :basename_(basename),flushEveryN_(flushEveryN),count_(0),mutex_(new MutexLock){
        file_.reset(new AppendFile(basename));
}

LogFile::~LogFile() {}

void LogFile::append(const char* logline,int len){
    MutexLockGuard lock(*mutex_);
    append_unlocked(logline,len);
}

void LogFile::flush(){
    MutexLockGuard lock(*mutex_);
    file_->flush();
}

void LogFile::append_unlocked(const char* logline,int len){
    file_->append(logline,len);
    ++count_;
    if(count_ >= flushEveryN_){
        count_ = 0;
        file_->flush();
    }
}