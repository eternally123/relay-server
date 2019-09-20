#include "tools.hpp"
#include "relayServer.hpp"

int openListenFd(int port, int listen_queue_num)
{
    int listenfd;
    struct sockaddr_in server_address;

    /* 创建套接字 */
    if ((listenfd = Socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
        return -1;

    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(port);

    /* bind 绑定套接字 */
    if (Bind(listenfd, (sockaddr*)&server_address, sizeof(server_address)) < 0)
        return -1;

    /* listen 监听 */
    if (Listen(listenfd, listen_queue_num) < 0)
        return -1;

    return listenfd;
}

int acceptClient(int listenfd)
{
    int connectfd;
    struct sockaddr_in client_address;
    socklen_t client_address_length;

    /* 与客户端建立连接 */
    if ((connectfd = Accept(listenfd, (sockaddr*)&client_address, &client_address_length)) < 0)
        return -1;

    return connectfd;
}

int openConnectfd(char* ip, int port)
{
    int socketfd;
    struct sockaddr_in server_address;
    /* 创建套接字 */
    if ((socketfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
        return -1;

    /* 和服务器连接 */
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr(ip);
    server_address.sin_port = htons(port);
    if (connect(socketfd, (struct sockaddr*)&server_address, sizeof(server_address)) < 0)
        return -1;

    return socketfd;
}

ssize_t readn(int fd, void* buff, size_t n)
{
    size_t nLeft;
    ssize_t nRead;
    char* ptr;

    ptr = (char*)buff;
    nLeft = n;
    while (nLeft > 0) {
        if ((nRead = read(fd, ptr, nLeft)) < 0) {
            if (errno == EINTR)
                nRead = 0;
            else
                return -1;
        } else if (nRead == 0) {
            break; //EOF
        }

        nLeft -= nRead;
        ptr += nRead;
    }
    return (n - nLeft);
}

ssize_t writen(int fd, const void* buff, size_t n)
{
    size_t nLeft;
    ssize_t nWritten;
    const char* ptr;

    ptr = (char*)buff;
    nLeft = n;
    while (nLeft > 0) {
        if ((nWritten = write(fd, ptr, nLeft)) <= 0) {
            if (nWritten < 0 && errno == EINTR)
                nWritten = 0;
            else
                return (-1);
        }

        nLeft -= nWritten;
        ptr += nWritten;
    }
    return (n);
}

ssize_t readline(int fd, void* buff, size_t maxLength)
{
    ssize_t n, readCount;
    char c, *ptr;
    ptr = (char*)buff;
    bool target = false;
    for (n = 1; n < maxLength; n++) {
        readCount = read(fd, &c, 1);

        if (readCount == 1) {
            *ptr++ = c;
            if (c == '\n') {
                target = true;
                break; //new line is stored
            }
        } else if (readCount == 0) { //EOF n-1 bytes were read
            *ptr = 0;
            return (n - 1);
        } else {
            if (errno == EINTR) {
                n = n - 1;
                continue;
            }
            return (-1); //error, errno set by read()
        }
    }
    *ptr = 0;
    return (n);
}

int Socket(int family, int type, int protocol)
{
    int n;
    if ((n = socket(family, type, protocol)) < 0)
        std::cout << "socket create error" << std::endl;
    return n;
}

int Bind(int fd, const struct sockaddr* socket_address, __socklen_t socket_length)
{
    if (bind(fd, socket_address, socket_length) == 0)
        return 0;
    std::cout << "bind error" << std::endl;
}

int Listen(int fd, int num)
{
    if (num == -1) {
        if (listen(fd, num) < 0) {
            std::cout << "listen error" << std::endl;
            return -1;
        }
    } else {
        if (listen(fd, num) < 0) {
            std::cout << "listen error" << std::endl;
            return -1;
        }
    }
    return 0;
}

int Accept(int fd, struct sockaddr* socket_address, __socklen_t* socket_length)
{
    int n;
    // std::cout << "Accept" << std::endl;
    n = accept(fd, socket_address, socket_length);
    // std::cout << "accept" << std::endl;

    if (n < 0) {
        if (errno = EPROTO || errno == ECONNABORTED) {
            std::cout << errno;
            return -1;
        } else {
            std::cout << "accept error" << std::endl;
            return -1;
        }
    } else {
        return n;
    }
}

int Connect(int fd, const struct sockaddr* socket_address, __socklen_t socket_length)
{
    if (connect(fd, socket_address, socket_length) == 0)
        return 0;
    std::cout << "connect error" << std::endl;
}

int setNoblock(int fd)
{
    int val;
    val = fcntl(fd, F_GETFL, 0);
    fcntl(fd, F_SETFL, val | O_NONBLOCK);
}