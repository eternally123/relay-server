#ifndef EPOLL_HPP_
#define EPOLL_HPP_
#include "relayServer.hpp"
#include "agentManager.hpp"

class Epoll {
public:
    Epoll();
    ~Epoll();
    void create();
    void run();
    void destory();

private:
    int wait(int timeout);
    void addEvent(int fd, int ev, void* pUserData);
    void modifyEvent(int fd, int ev, void* pUserData);
    void removeEvent(int fd);

private:
    int m_epollFd;
    int m_port;
    int m_epollSize;
    epoll_event* m_epollEvents;
    AgentManager* m_agentManager;
};

#endif