#include "transAgent.hpp"
#include "listenAgent.hpp"
#include "relayServer.hpp"
#include "tools.hpp"
#include "netinet/in.h"


ListenAgent::ListenAgent() {
}

ListenAgent::~ListenAgent() {
}

Agent *ListenAgent::accept() {
    sockaddr_in clientAddress;
    memset(&clientAddress, 0, sizeof(clientAddress));
    int newFd = Accept(m_socketFd, (sockaddr *) &clientAddress, reinterpret_cast<__socklen_t *>(sizeof(clientAddress)));

    return ((Agent *) (new TransAgent()));
}

int ListenAgent::getSocketFd() {
    return m_socketFd;
}

int ListenAgent::send() {

}

int ListenAgent::receive() {

}
