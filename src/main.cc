#include "relayServerHeader.hpp"

int main()
{
    Epoll epoll;
    epoll.create();
    epoll.run();
}