#include "TcpServer.h"

TcpServer::TcpServer():
    m_port(0),
    m_sock(0),
    m_clientCount(0)
{
}

TcpServer::~TcpServer()
{
}

int TcpServer::Start(int port)
{
    m_port = port;

    // Winsock initialize
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 0), &wsaData) != 0)
    {
        return -1;
    }

    // Create socket
    m_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (m_sock == INVALID_SOCKET)
    {
        return -1;
    }

    // Bind
    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(m_port);
    addr.sin_addr.S_un.S_addr = INADDR_ANY;
    if (bind(m_sock, (sockaddr *)&addr, sizeof(addr)) == SOCKET_ERROR)
    {
        return -1;
    }

    // Listen
    if (listen(m_sock, SOMAXCONN) == SOCKET_ERROR)
    {
        return -1;
    }

    // Create thread
    m_thread = std::thread(&TcpServer::Thread, this);

    return 0;
}

int TcpServer::Stop()
{
    // Close socket
    closesocket(m_sock);

    // Winsock finalize
    WSACleanup();

    // Wait for thread to finish
    m_thread.join();

    return 0;
}

void TcpServer::Thread()
{
    while (true)
    {
        Accept();
    }
}

/**
 * @brief Accept function
 * @details accept client connection
 * mutiple clients can connect to the server.
 * another thread is created for each client.
 */
void TcpServer::Accept()
{
    // Accept
    sockaddr_in client;
    int len = sizeof(client);
    SOCKET sock = accept(m_sock, (sockaddr *)&client, &len);
    if (sock == INVALID_SOCKET)
    {
        return;
    }

    // Create thread
    std::thread thread(&TcpServer::Receive, this, sock);
    thread.detach();

    // Increment client count
    m_clientCount++;
}

/**
 * @brief Receive function
 * @details receive data from client
 * receive data from client and don't send it back to client.
 * After connection, there is always incoming data.
 * @param[in] client socket
 */
void TcpServer::Receive(SOCKET client)
{
    // Receive
    char buf[1024];
    while (true)
    {
        int size = recv(client, buf, sizeof(buf), 0);
        if (size <= 0)
        {
            break;
        }
    }

    // Close socket
    closesocket(client);

    // Decrement client count
    m_clientCount--;
}