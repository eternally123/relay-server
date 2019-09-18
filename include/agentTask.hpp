#ifndef AGENTTASK_HPP_
#define AGENTTASK_HPP_

#include "relayServer.hpp"
#include "buffer.hpp"

class AgentTask {
public:
    AgentTask(int destId, int bufSize);
    ~AgentTask();

    int generateTask(char* start, char* end);
    int sendTaskToBuffer(Buffer* buffer);

private:
    int m_destId;
    int m_bufSize;
    char* m_buf;
};

#endif