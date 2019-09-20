#include "relayServerHeader.hpp"

int main() {
    Epoll epoll = Epoll(10000);
    epoll.create();
    epoll.run();
}