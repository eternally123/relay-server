#include <agentTask.hpp>
#include <buffer.hpp>
#include "relayServer.hpp"

AgentTask::AgentTask(int destId, int bufSize)
{
    m_destId = destId;
    m_bufSize = bufSize;
    m_buf = new char[bufSize];
}

AgentTask::~AgentTask()
{
    if (m_buf != NULL)
        delete[] m_buf;
}

int AgentTask::generateTask(char* start, char* end)
{
    if ((end - start) != m_bufSize)
        return -1;
    memcpy(m_buf, start, end - start);
    return end - start;
}

int AgentTask::sendTaskToBuffer(Buffer* buffer)
{
    memcpy(buffer->m_writeStart, m_buf, m_bufSize);
    return m_bufSize;
}