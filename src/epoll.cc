#include "listenAgent.hpp"
#include "relayServer.hpp"
#include <epoll.hpp>
#include <tools.hpp>

Epoll::Epoll(int port)
        : m_epollFd(-1), m_listenFd(-1) {
    m_port = port;
    m_epollSize = EPOLL_MAXHANDLE_SIZE;
    m_epollEvents = new epoll_event[m_epollSize];
    m_agentManager = new AgentManager();
}

Epoll::~Epoll() {
    if (m_epollEvents != NULL)
        delete[] m_epollEvents;
    if (m_agentManager != NULL)
        delete m_agentManager;
}

void Epoll::create() {
    m_listenFd = openListenFd(m_port, LISTEN_QUEUE_SIZE);//m_listenFd
    std::cout << "create success,m_listenFd:" << m_listenFd << std::endl;

    if ((m_epollFd = epoll_create(m_epollSize)) < 0) {//m_epollFd
        std::cerr << "epoll_create failed" << std::endl;
        exit(1);
    }

    ListenAgent *listenAgent = new ListenAgent(m_listenFd);
    addEvent(m_listenFd, EPOLLIN, (void *) listenAgent);

    return;
}

void Epoll::run() {
    int numReady;
    epoll_event event;
    Agent *agent = NULL;
    while (1) {
        numReady = wait(EPOLL_TIMEOUT);
        std::cout << "ready socket num:" << numReady << std::endl;
        for (int i = 0; i < numReady; i++) {
            event = m_epollEvents[i]; //获取event
            agent = (Agent *) event.data.ptr;
            if (agent->getSocketFd() == m_listenFd) {
                //listenFd
                Agent *newAgent = agent->accept();
                m_agentManager->login(newAgent);
            } else {
                if (event.events || EPOLLIN)
                    agent->receive();
                if (event.events || EPOLLOUT)
                    agent->send();
            }
        }
        m_agentManager->recycle();
    }
}

int Epoll::wait(int timeout) {
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

void Epoll::addEvent(int fd, int ev, void *pUserData) {
    epoll_event event;
    event.data.ptr = pUserData;
    event.events = ev;
    epoll_ctl(m_epollFd, EPOLL_CTL_ADD, fd, &event);
}

void Epoll::modifyEvent(int fd, int ev, void *pUserData) {
    epoll_event event;
    event.data.ptr = pUserData;
    event.events = ev;
    epoll_ctl(m_epollFd, EPOLL_CTL_MOD, fd, &event);
}

void Epoll::removeEvent(int fd) {
    epoll_ctl(m_epollFd, EPOLL_CTL_DEL, fd, 0);
}