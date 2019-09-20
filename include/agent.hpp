#ifndef AGENT_HPP_
#define AGENT_HPP_

#include "relayServer.hpp"

#include "agentTask.hpp"
#include "buffer.hpp"
#include "message.hpp"

class Agent {
    friend class AgentManager;

public:
    Agent() {};

    virtual ~Agent() {};

    virtual int receive() {return 0;};

    virtual int send() {return 0;};

    virtual Agent *accept() {return 0;};

    virtual int getSocketFd() {return 0;};

protected:
    Head *m_head;
    Buffer *m_buffer;
    int m_socketFd;
    typedef std::list<AgentTask *> taskList;
    taskList m_readTaskList, m_writeTaskList;
    //    taskList* t;
};

#endif