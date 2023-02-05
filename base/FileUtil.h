/*
 * @Author: zhongxian.chen
 * @Date: 2023-01-10 21:17:53
 * @LastEditors: zhongxian.chen
 * @LastEditTime: 2023-01-10 21:21:49
 * @Description: 
 * 
 * Copyright (c) 2023 by zhongxian.chen, All Rights Reserved. 
 */
#ifndef BASE_FILEUTIL_H
#define BASE_FILEUTIL_H

#include "noncopyable.h"

#include <string>
class AppendFile : noncopyable{
public:
    explicit AppendFile(std::string filename);
     ~AppendFile();
     void append(const char* logline,const size_t len);
     void flush();
private:
    size_t write(const char* logline,size_t len);
    FILE* fp_;
    char buffer_[64 * 1024];
};
#endif