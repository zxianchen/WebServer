/*
 * @Author: zhongxian.chen
 * @Date: 2023-02-18 22:20:17
 * @LastEditors: zhongxian.chen
 * @LastEditTime: 2023-02-18 22:24:11
 * @Description: 
 * 
 * Copyright (c) 2023 by zhongxian.chen, All Rights Reserved. 
 */
#ifndef BASE_LOGGING_H
#define BASE_LOGGING_H

#include "LogStream.h"

#include <pthread.h>
#include <stdio.h>
#include <string>
#include <string.h>

class AsyncLogging;

class Logger {
 public:
  Logger(const char *fileName, int line);
  ~Logger();
  LogStream &stream() { return impl_.stream_; }

  static void setLogFileName(std::string fileName) { logFileName_ = fileName; }
  static std::string getLogFileName() { return logFileName_; }

 private:
  class Impl {
   public:
    Impl(const char *fileName, int line);
    void formatTime();

    LogStream stream_;
    int line_;
    std::string basename_;
  };
  Impl impl_;
  static std::string logFileName_;
};

#define LOG Logger(__FILE__, __LINE__).stream()
#endif