/*
 * @Author: zhongxian.chen
 * @Date: 2022-12-27 20:28:25
 * @LastEditors: zhongxian.chen
 * @LastEditTime: 2022-12-28 22:14:03
 * @Description: 
 * 
 * Copyright (c) 2022 by zhongxian.chen, All Rights Reserved. 
 */
#include "base/CurrentThread.h"
#include "base/Thread.h"
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
    Thread th(func);
    th.start();
    std::cout<<CurrentThread::tid()<<std::endl;
    std::cout<<"Hello World!"<<std::endl;
}