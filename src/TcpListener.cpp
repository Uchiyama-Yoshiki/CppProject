#include "TcpListener.h"

TcpListener::TcpListener() : m_sock(NULL),
                             m_port(0)
{
    Init();
}

TcpListener::~TcpListener()
{
    Close();
}

void TcpListener::Init()
{
    // Winsock initialize
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        return;
    }
}

void TcpListener::Close()
{
    shutdown(m_sock, SD_BOTH);
    closesocket(m_sock);
}

void TcpListener::Listen(int port, int waitConnection)
{
    // Create socket
    m_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (m_sock == INVALID_SOCKET)
    {
        WSACleanup();
        return;
    }

    // Bind
    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(m_port);
    addr.sin_addr.S_un.S_addr = INADDR_ANY;
    if (bind(m_sock, (sockaddr *)&addr, sizeof(addr)) == SOCKET_ERROR)
    {
        WSACleanup();
        return;
    }

    // keepalive
    int optval = 1;
    setsockopt(m_sock, SOL_SOCKET, SO_KEEPALIVE, (char *)&optval, sizeof(optval));

    // Listen
    if (listen(m_sock, SOMAXCONN) == SOCKET_ERROR)
    {
        WSACleanup();
        return;
    }
}

SOCKET TcpListener::Accept()
{
    if (m_sock == NULL)
    {
        throw std::runtime_error("Socket is not initialized.");
        return NULL;
    }

    // Accept
    sockaddr_in client;
    int len = sizeof(client);
    SOCKET sock = accept(m_sock, (sockaddr *)&client, &len);
    if (sock == INVALID_SOCKET)
    {
        WSACleanup();
        return NULL;
    }

    return sock;
}