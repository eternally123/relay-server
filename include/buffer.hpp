#ifndef BUFFER_HPP_
#define BUFFER_HPP_

class Buffer {
public:
    bool m_onceReadFinish;
    bool m_onceWriteFinish;
    char *m_readBuf, *m_writeBuf;
    char *m_readStart, *m_readEnd;
    char *m_writeStart, *m_writeEnd;
    int m_readSize, m_writeSize;

public:
    Buffer();
    ~Buffer();
    bool isReadable();
    bool isWriteable();
    int read_noblock(int fd);
    int write_noblock(int fd);
};

#endif