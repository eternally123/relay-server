#ifndef AGENT_HPP_
#define AGENT_HPP_

#include "relayServer.hpp"

#include "message.hpp"
#include "buffer.hpp"
#include "agentTask.hpp"

class Agent {
    friend class AgentManager;

public:
    Agent(){};
    virtual ~Agent(){};

    virtual int receive() = 0;
    virtual int send() = 0;

protected:
    Head* m_head;
    Buffer* m_buffer; //?初始值是什么
    int m_socketFd;
    typedef std::list<AgentTask*> taskList;
    taskList m_readTaskList, m_writeTaskList;
//    taskList* t;
};

#endif