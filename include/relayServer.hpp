#ifndef RELAYSERVER_HPP_
#define RELAYSERVER_HPP_

///* 头文件 */
//#include "agent.hpp"
//#include "agentManager.hpp"
//#include "agentTask.hpp"
//#include "buffer.hpp"
//#include "epoll.hpp"
//#include "message.hpp"
//#include "tools.hpp"
//#include "transAgent.hpp"


/* c */
#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <unistd.h>

/* cpp */
#include <iostream>
#include <list>
#include <map>

/* 常量 */
#ifndef BUFFER_SIZE
#define BUFFER_SIZE 4096
#endif

#ifndef LISTEN_QUEUE_SIZE
#define LISTEN_QUEUE_SIZE 4096
#endif

#ifndef EPOLL_TIMEOUT
#define EPOLL_TIMEOUT 5000
#endif

#ifndef EPOLL_MAXHANDLE_SIZE
#define EPOLL_MAXHANDLE_SIZE 5000
#endif

#endif