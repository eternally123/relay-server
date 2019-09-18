#ifndef MESSAGE_HPP_
#define MESSAGE_HPP_
#include "relayServer.hpp"
class Head {
public:
    int srcId;
    int destId;
    int bodyLength;
    int status;
};

#endif