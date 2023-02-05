/*
 * @Author: zhongxian.chen
 * @Date: 2022-12-27 20:28:25
 * @LastEditors: zhongxian.chen
 * @LastEditTime: 2023-01-10 21:42:15
 * @Description: 
 * 
 * Copyright (c) 2022 by zhongxian.chen, All Rights Reserved. 
 */
#include "base/CurrentThread.h"
#include "base/Thread.h"
#include "base/FileUtil.h"
#include <iostream>
#include <unistd.h>
void func(){
    for(int i = 0 ; i < 20 ; i++)
    {
        std::cout<<i<<std::endl;
        sleep(1);
    }
}
int main(){
    // Thread th(func);
    // th.start();
    std::cout<<CurrentThread::tid()<<std::endl;
    std::cout<<"Hello World!"<<std::endl;
    AppendFile  log("test.log");
    log.append("Hello World",12);
}