#include "TcpReceiver.h"

TcpReceiver::TcpReceiver(SOCKET sock):
    m_sock(sock)
{
}

TcpReceiver::~TcpReceiver()
{
    Close();
}


void TcpReceiver::Close()
{
    shutdown(m_sock, SD_BOTH);
    closesocket(m_sock);
}

bool TcpReceiver::Receive(char *buf, int size)
{
    // Receive
    int ret = recv(m_sock, buf, sizeof(buf), 0);
    if (ret == SOCKET_ERROR)
    {
        return false;
    }
    else if (ret == 0)
    {
        return false;
    }
    else
    {
        std::cout << buf << std::endl;
        return true;
    }
}

bool TcpReceiver::Receive(std::vector<char> &buf)
{
    // Receive
    int ret = recv(m_sock, buf.data(), buf.size(), 0);
    if (ret == SOCKET_ERROR)
    {
        return false;
    }
    else if (ret == 0)
    {
        return false;
    }
    else
    {
        std::cout << buf.data() << std::endl;
        return true;
    }
}