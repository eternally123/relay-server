#ifndef AGENTMANAGER_HPP_
#define AGENTMANAGER_HPP_
#include "relayServer.hpp"
#include "agent.hpp"
#include <buffer.hpp>

class AgentManager {
public:
    AgentManager();
    ~AgentManager();

    int generateId();
    int login(Agent* agent);
    int logout(int id);
    Agent* searchById(int id);

    int recycle();

private:
    // bool copyable(Agent* src, Agent* dest);
    // void copyMessage(Agent* src, Agent* dest);

    typedef std::map<int, Agent*> AgentMap;
    AgentMap agentMap;
    int nextId;
};

#endif
