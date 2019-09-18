#include <agentManager.hpp>
#include <agent.hpp>
#include "relayServer.hpp"

AgentManager::AgentManager()
{
    nextId = 1;
}

AgentManager::~AgentManager()
{
}

int AgentManager::generateId()
{
    return nextId++;
}

int AgentManager::login(Agent* agent)
{
    int id = generateId();
    agentMap[id] = agent;
    return id;
}

int AgentManager::logout(int id)
{
    agentMap.erase(id);
    return 1;
}

Agent* AgentManager::searchById(int id)
{
    return agentMap[id];
}

int AgentManager::recycle()
{
    AgentMap::iterator iter;
    Agent *srcAgent, *destAgent;
    iter = agentMap.begin();
    AgentTask* agentTask;
    while (iter != agentMap.end()) {
        srcAgent = iter->second;
        int destId = srcAgent->m_head->destId;
        destAgent = agentMap[destId];


        agentTask = srcAgent->m_readTaskList.front();
        srcAgent->m_readTaskList.pop_front();
        destAgent->m_writeTaskList.push_back(agentTask);
    }

    return 0;
}

// bool AgentManager::copyable(Agent* src, Agent* dest)
// {
//     if (dest->m_buffer->m_writeSize != 0)
//         return false;
//     if (src->m_buffer->m_readSize() == 0)
//         return false;

//     return true;
// }

// void AgentManager::copyMessage(Agent* src, Agent* dest)
// {
//     Buffer* srcBuf = src->m_buffer;
//     Buffer* destBuf = dest->m_buffer;
//     memcpy(destBuf->m_writeStart, srcBuf->m_readStart, srcBuf->m_readSize);
//     return;
// }