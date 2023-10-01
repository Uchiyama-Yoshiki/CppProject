#pragma once
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <cstdio>
#include <vector>
#include <iostream>

#pragma comment(lib,"ws2_32.lib")

class TcpReceiver
{
private:
    SOCKET m_sock;
    int m_port;
    void Init();
public:
    /**
     * @brief Construct a new Tcp Receiver object
     */
    TcpReceiver(SOCKET sock);

    /**
     * @brief Destroy the Tcp Receiver object
     * 
     */
    ~TcpReceiver();

    /**
     * @brief Close
     * 
     */
    void Close();

/**
 * @brief Receive
 * 
 */
    void Receive();

    /**
     * @brief Receive
     * 
     * @param buf 
     * @param size 
     * @return true 
     * @return false 
     */
    bool Receive(char *buf, int size);

    /**
     * @brief Receive
     * 
     * @param buf 
     * @return true 
     * @return false 
     */
    bool Receive(std::vector<char> &buf);
};