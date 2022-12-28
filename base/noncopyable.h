/*
 * @Author: zhongxian.chen
 * @Date: 2022-12-27 20:51:21
 * @LastEditors: zhongxian.chen
 * @LastEditTime: 2022-12-27 20:56:38
 * @Description: 
 * 
 * Copyright (c) 2022 by zhongxian.chen, All Rights Reserved. 
 */
#ifndef BASE_NONCOPYABLE_H
#define BASE_NONCOPYABLE_H

class noncopyable
{
public:
    noncopyable(const noncopyable&) = delete;
    void operator=(const noncopyable&) = delete;
protected:
    noncopyable() = default;
    ~noncopyable() = default;
};

#endif 