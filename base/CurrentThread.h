/*
 * @Author: zhongxian.chen
 * @Date: 2022-12-28 20:18:02
 * @LastEditors: zhongxian.chen
 * @LastEditTime: 2022-12-28 21:03:52
 * @Description: 
 * 
 * Copyright (c) 2022 by zhongxian.chen, All Rights Reserved. 
 */
#ifndef BASE_CURRENTTHREAD_H
#define BASE_CURRENTTHREAD_H

namespace CurrentThread{
extern __thread int t_cachedTid;
extern __thread char t_tidString[32];
extern __thread int t_tidStringLength;
extern __thread const char* t_threadName;
void cacheId();
inline int tid(){
    if(__builtin_expect(t_cachedTid == 0,0)){
        cacheId();
    }
    return t_cachedTid;
}
inline const char* tidString(){
    return t_tidString;
}
inline int tidStringLength(){
    return t_tidStringLength;
}
inline const char* name(){
    return t_threadName;
}
}

#endif