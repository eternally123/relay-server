#include "transAgent.hpp"
#include "listenAgent.hpp"
#include "relayServer.hpp"
#include "tools.hpp"
#include "netinet/in.h"


ListenAgent::ListenAgent(int socketFd) {
    m_socketFd = socketFd;
}

ListenAgent::~ListenAgent() {
}

Agent *ListenAgent::accept() {
    sockaddr_in clientAddress;
    memset(&clientAddress, 0, sizeof(clientAddress));
    int newFd = Accept(m_socketFd, (sockaddr *) &clientAddress, (__socklen_t*)(sizeof(clientAddress)));

    return ((Agent *) (new TransAgent(newFd)));
}

int ListenAgent::getSocketFd() {
    return m_socketFd;
}

int ListenAgent::send() {
    return 0;
}

int ListenAgent::receive() {
    return 0;
}
