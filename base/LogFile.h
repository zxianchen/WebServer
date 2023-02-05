/*
 * @Author: zhongxian.chen
 * @Date: 2023-02-05 18:22:42
 * @LastEditors: zhongxian.chen
 * @LastEditTime: 2023-02-05 18:29:06
 * @Description: 
 * 
 * Copyright (c) 2023 by zhongxian.chen, All Rights Reserved. 
 */
#ifndef BASE_LOGFILE_H
#define BASE_LOGFILE_H

#include <memory>
#include <string>

#include "FileUtil.h"
#include "MutexLock.h"
#include "noncopyable.h"

class LogFile : noncopyable{
public:
    LogFile(const std::string& basename,int flushEaveryN = 1024);
    ~LogFile();

    void append(const char* logline,int len);
    void flush();
    bool rollFile();
private:
    void append_unlocked(const char* logline,int len);

    const std::string basename_;
    const int flushEveryN_;
    int count_;
    std::unique_ptr<MutexLock> mutex_;
    std::unique_ptr<AppendFile> file_;
};
#endif
