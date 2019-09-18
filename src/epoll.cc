#include <epoll.hpp>
#include <tools.hpp>
#include "relayServer.hpp"

Epoll::Epoll()
{
    m_epollEvents = NULL;
}

Epoll::~Epoll()
{
    if (m_epollEvents != NULL)
        delete[] m_epollEvents;
}

void Epoll::create()
{
    int listenFd = openListenfd(m_port, LISTEN_QUEUE_SIZE);

    if ((m_epollFd = epoll_create(EPOLL_MAXHANDLE_SIZE)) < 0) {
        std::cerr << "epoll_create failed" << std::endl;
        exit(1);
    }

    return;
}

void Epoll::run()
{
    int numReady;
    epoll_event event;
    Agent* agent = NULL;

    numReady = wait(EPOLL_TIMEOUT);
    for (int i = 0; i < numReady; i++) {
        event = m_epollEvents[i]; //获取event
        agent = (Agent*)event.data.ptr;
        if (event.events || EPOLLIN)
            agent->receive();
        if (event.events || EPOLLOUT)
            agent->send();
    }

    m_agentManager->recycle();
}

int Epoll::wait(int timeout)
{
    int numReady;
    while (1) {
        numReady = epoll_wait(m_epollFd, m_epollEvents, EPOLL_MAXHANDLE_SIZE, EPOLL_TIMEOUT);
        if (numReady < 0) {
            if (errno == EINTR)
                continue;
            else {
                std::cerr << "Epoll::wait() error" << std::endl;
                exit(1);
            }
        } else {
            return numReady;
        }
    }
}

void Epoll::addEvent(int fd, int ev, void* pUserData)
{
    epoll_event event;
    event.data.ptr = pUserData;
    event.events = ev;
    epoll_ctl(m_epollFd, EPOLL_CTL_ADD, fd, &event);
}

void Epoll::modifyEvent(int fd, int ev, void* pUserData)
{
    epoll_event event;
    event.data.ptr = pUserData;
    event.events = ev;
    epoll_ctl(m_epollFd, EPOLL_CTL_MOD, fd, &event);
}

void Epoll::removeEvent(int fd)
{
    epoll_ctl(m_epollFd, EPOLL_CTL_DEL, fd, 0);
}