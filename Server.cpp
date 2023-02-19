/*
 * @Author: zhongxian.chen
 * @Date: 2023-02-19 15:18:17
 * @LastEditors: zhongxian.chen
 * @LastEditTime: 2023-02-19 16:43:44
 * @Description:
 *
 * Copyright (c) 2023 by zhongxian.chen, All Rights Reserved.
 */
#include "Server.h"
#include "Utils.h"
#include "base/Logging.h"

#include <arpa/inet.h>
#include <netinet/in.h>
#include <functional>
#include <sys/socket.h>
#include <iostream>
Server::Server(EventLoop *loop, int threadNum, int port)
    : loop_(loop),
      threadNum_(threadNum),
      eventLoopThreadPool_(new EventLoopThreadPool(loop_, threadNum)),
      started_(false),
      acceptChannel_(new Channel(loop_)),
      port_(port),
      listenFd_(socket_bind_listen(port_))
{
    acceptChannel_->setFd(listenFd_);
    handle_for_sigpipe();
    if (setSocketNonBlocking(listenFd_) < 0)
    {   
        perror("set socket non block failed");
        abort();
    }
}

void Server::start()
{
    eventLoopThreadPool_->start();
    acceptChannel_->setEvents(EPOLLIN | EPOLLET);
    acceptChannel_->setReadHandler(std::bind(&Server::handNewConn, this));
    acceptChannel_->setConnHandler(std::bind(&Server::handThisConn, this));
    loop_->addToPoller(acceptChannel_, 0);
    started_ = true;
}

void Server::handNewConn()
{
    struct sockaddr_in client_addr;
    memset(&client_addr, 0, sizeof(struct sockaddr_in));
    socklen_t client_addr_len = sizeof(client_addr);
    int accept_fd = 0;
    while ((accept_fd = accept(listenFd_, (struct sockaddr *)&client_addr, &client_addr_len)) > 0)
    {
        EventLoop *loop = eventLoopThreadPool_->getNextLoop();
        LOG << "New connection from " << inet_ntoa(client_addr.sin_addr) << ":"
            << ntohs(client_addr.sin_port);

        if (accept_fd >= MAXFDS)
        {
            close(accept_fd);
            continue;
        }
        setSocketNodelay(accept_fd);
        std::shared_ptr<HttpData> req_info(new HttpData(loop, accept_fd));
        req_info->getChannel()->setHolder(req_info);
        loop->queueInLoop(std::bind(&HttpData::newEvent, req_info));
    }
    acceptChannel_->setEvents(EPOLLIN | EPOLLET);
}