cmake_minimum_required(VERSION 2.8)

project(WebServer)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

#  set(CMAKE_CXX_COMPILER "g++")
#  set(CMAKE_CXX_FLAGS_DEBUG "-O0")
#  set(CMAKE_CXX_FLAGS_RELEASE "-O0")

 set(CXX_FLAGS
    -g
    -Wall
    -std=c++11
    -D_PTHREADS
    -Wno-unused-parameter
)
set(WebServerSrc
    base/AsyncLogging.cpp
    base/CountDownLatch.cpp
    base/FIleUtil.cpp
    base/LogFile.cpp
    base/LogStream.cpp
    base/Thread.cpp
    base/Logging.cpp
    Channel.cpp
    Epoll.cpp
    EventLoop.cpp
    EventLoopThread.cpp
    EventLoopThreadPool.cpp
    HttpData.cpp
    Server.cpp
    Timer.cpp
   # Utils.cpp
    main.cpp
)

add_executable(WebServer ${WebServerSrc})
target_link_libraries(WebServer pthread)