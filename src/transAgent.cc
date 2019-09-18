#include <transAgent.hpp>
#include <message.hpp>
#include <buffer.hpp>
#include "relayServer.hpp"

TransAgent::TransAgent()
{
    m_head = new Head();
    m_buffer = new Buffer();
}

TransAgent::~TransAgent()
{
    if (m_buffer != NULL)
        delete[] m_buffer;
}

int TransAgent::receive()
{
    int n;
    if (m_buffer->m_onceReadFinish == true) {
        n = readHeader();
        if (n != sizeof(Head)) {
            //协议出问题或者有人恶意攻击
            return -1; //告诉上层函数此连接不安全，关闭。
        }
    }
    if (m_buffer->m_onceReadFinish == false)
        n = readBody();

    if (m_buffer->m_readSize == m_head->bodyLength) {
        //读取完客户端一次请求，将任务加入到taskList中
        AgentTask* agentTask = new AgentTask(m_head->destId, m_buffer->m_readSize);
        agentTask->generateTask(m_buffer->m_readStart, m_buffer->m_readEnd);
        m_readTaskList.push_back(agentTask);

        m_buffer->m_onceReadFinish = true;
    }
    return n;
}

int TransAgent::send()
{
    int n;
    if (m_buffer->m_onceWriteFinish == false) {
        //此次task尚未做完
        n = m_buffer->write_noblock(m_socketFd);
    }
    if (m_buffer->m_writeEnd == m_buffer->m_writeStart) {
        //task finish
        if (m_writeTaskList.size() != 0) {
            AgentTask* agentTask = m_writeTaskList.front();
            m_writeTaskList.pop_front();
            agentTask->sendTaskToBuffer(m_buffer);
        }
    }
    return n;
}

int TransAgent::readHeader()
{
    int n = read(m_socketFd, m_head, sizeof(Head));
    if (n != sizeof(Head)) {
        return -1;
    }
    m_buffer->m_onceReadFinish = false;
    return 0;
}

int TransAgent::readBody()
{
    int n = m_buffer->read_noblock(m_socketFd);
    return n;
}