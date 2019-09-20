#ifndef TRANSAGENT_HPP_
#define TRANSAGENT_HPP_
#include "relayServer.hpp"
#include "agent.hpp"

class TransAgent:public Agent {
    friend class AgentManager;

public:
    TransAgent(int socketFd);
    virtual ~TransAgent();

    virtual int receive();
    virtual int send();

private:
    int readHeader();
    int readBody();

    int generateTask();
};

#endif