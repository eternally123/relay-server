#include <buffer.hpp>
#include "relayServer.hpp"

Buffer::Buffer()
{
    m_onceReadFinish = true;
    m_onceWriteFinish = true;
    m_readSize = m_writeSize = 0;
    m_readBuf = new char[BUFFER_SIZE];
    m_writeBuf = new char[BUFFER_SIZE];
    m_readStart = m_readEnd = m_readBuf;
    m_writeStart = m_writeEnd = m_writeBuf;
}

Buffer::~Buffer()
{
    delete[] m_readBuf;
    delete[] m_writeBuf;
}

bool Buffer::isReadable()
{
    if (m_readEnd != &m_readBuf[m_readSize - 1])
        return true;
    return false;
}

bool Buffer::isWriteable()
{
    if (m_writeEnd != &m_writeBuf[m_writeSize - 1])
        return true;
    return false;
}

int Buffer::read_noblock(int fd)
{
    int n;
    int left = &m_readBuf[m_readSize - 1] - m_readEnd + 1;
    if ((n = ::read(fd, m_readEnd, left)) < 0) {
        if ((errno != EWOULDBLOCK) && (errno != EAGAIN)) {
            printf("read error \n");
            exit(1);
        }
    } else if (n > 0) {
        m_readEnd += n;
    }
    m_readSize += n;
    return n;
}

int Buffer::write_noblock(int fd)
{
    int n;
    int left = m_writeEnd - m_writeStart;

    if ((n = ::write(fd, m_writeStart, left)) < 0) {
        if ((errno != EWOULDBLOCK) && (errno != EAGAIN)) {
            printf("write error\n");
            exit(1);
        }
    } else if (n > 0) {
        m_writeStart += n;
        if (m_writeStart == m_writeEnd) {
            m_writeStart = m_writeBuf;
            m_writeEnd = m_writeBuf;
        }
    }
    m_writeSize += n;
    return n;
}