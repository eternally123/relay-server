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

    virtual int receive() {};

    virtual int send() {};

    virtual Agent *accept() {};

    virtual int getSocketFd() {};

protected:
    Head *m_head;
    Buffer *m_buffer; //?初始值是什么
    int m_socketFd;
    typedef std::list<AgentTask *> taskList;
    taskList m_readTaskList, m_writeTaskList;
    //    taskList* t;
};

#endif