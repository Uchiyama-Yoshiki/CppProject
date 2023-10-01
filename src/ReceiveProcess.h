#pragma once
#include <thread>
#include <vector>
#include <map>
#include <string>
#include <iostream>
#include "TcpListener.h"
#include "TcpReceiver.h"

struct ClientInfo
{
    TcpReceiver sock;
    std::string ip;
};

class ReceiveProcess
{
private:
    TcpListener m_listener;
    std::vector<TcpReceiver> m_socks;
    std::thread m_listenThread;
    std::vector<std::thread> m_recvThreads;
    bool m_isRunning;
    int m_port;
    int m_maxClientNum;
    // std::map<std::string,ClientInfo> g_clientList;
    // std::vector<ClientInfo> g_clientList;

    void ListenWorker();
    void RecvWorker(SOCKET sock);
public:
    ReceiveProcess(int port,int maxClientNum);
    ~ReceiveProcess();

    void Run();
    void Stop();
    };