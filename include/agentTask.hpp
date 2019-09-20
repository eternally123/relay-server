#ifndef AGENTTASK_HPP_
#define AGENTTASK_HPP_

#include "relayServer.hpp"
#include "buffer.hpp"

class AgentTask {
public:
    AgentTask(int srcId, int destId, int bufSize);

    ~AgentTask();

    int getDestId();

    int generateTask(char *start, char *end);

    int sendTaskToBuffer(Buffer *buffer);

private:
    int m_srcId;
    int m_destId;
    int m_bufSize;
    char *m_buf;
};

#endif