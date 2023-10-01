#pragma once
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdexcept>
#pragma comment(lib,"ws2_32.lib")
/**
 * @brief  TCP listener class
 * @details  This class is a TCP listener class.
 */
class TcpListener
{
private:
    SOCKET m_sock;
    int m_port;
    void Init();

public:
    /**
     * @brief Construct a new Tcp Listener object
     */
    TcpListener();

    /**
     * @brief Destroy the Tcp Listener object
     *
     */
    ~TcpListener();

    /**
     * @brief start listening
     * @param[in] port
     * @param[in] waitConnection
     */
    void Listen(int port, int waitConnection);

    /**
     * @brief Close
     *
     */
    void Close();

    /**
     * @brief Accept
     *
     */
    SOCKET Accept();
};