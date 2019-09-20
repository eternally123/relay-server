#ifndef LISTENAGENT_HPP_
#define LISTENAGENT_HPP_

#include "agent.hpp"

class ListenAgent : public Agent {
public:
    ListenAgent(int socketFd);

    virtual ~ListenAgent();

    virtual Agent *accept();

    virtual int getSocketFd();

    virtual int receive();

    virtual int send();
};

#endif