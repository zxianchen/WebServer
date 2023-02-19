/*
 * @Author: zhongxian.chen
 * @Date: 2023-02-19 15:49:22
 * @LastEditors: zhongxian.chen
 * @LastEditTime: 2023-02-19 16:44:43
 * @Description: 
 * 
 * Copyright (c) 2023 by zhongxian.chen, All Rights Reserved. 
 */
#include "Server.h"
#include "base/Logging.h"
#include "EventLoop.h"
#include <getopt.h>
#include <string>

int main(int argc, char *argv[]) {
  int threadNum = 2;
  int port = 9006;
  std::string logPath = "./WebServer.log";

  // parse args
  int opt;
  const char *str = "t:l:p:";
  while ((opt = getopt(argc, argv, str)) != -1) {
    switch (opt) {
      case 't': {
        threadNum = atoi(optarg);
        break;
      }
      case 'l': {
        logPath = optarg;
        if (logPath.size() < 2 || optarg[0] != '/') {
          printf("logPath should start with \"/\"\n");
          abort();
        }
        break;
      }
      case 'p': {
        port = atoi(optarg);
        break;
      }
      default:
        break;
    }
  }
  Logger::setLogFileName(logPath);
  EventLoop mainLoop;
  Server myHTTPServer(&mainLoop, threadNum, port);
  myHTTPServer.start();
  mainLoop.loop();
  return 0;
}
