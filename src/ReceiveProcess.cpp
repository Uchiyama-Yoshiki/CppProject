#include "ReceiveProcess.h"

ReceiveProcess::ReceiveProcess(int port,int maxClientNum):
    m_port(port),
    m_maxClientNum(maxClientNum),
    m_isRunning(false)
{
    try
    {
        m_listener = TcpListener();
    }
    catch(const std::exception& e)
    {
    }
}

ReceiveProcess::~ReceiveProcess()
{
    Stop();
}

void ReceiveProcess::Run()
{
    m_isRunning = true;
    m_listenThread = std::thread(&ReceiveProcess::ListenWorker, this);
}

void ReceiveProcess::Stop()
{   
    m_isRunning = false;

    // listener close
    // TcpListener::Accept() is blocking, 
    // so close the socket first
    m_listener.Close();
    if(m_listenThread.joinable())
    {
        m_listenThread.join();
    }

    // clientList close
    // TcpReceiver::Receive() is blocking,
    // so close the socket first
    for(auto &sock : m_socks)
    {
        sock.Close();
    }
    for(auto &thread : m_recvThreads)
    {
        if(thread.joinable())
        {
            thread.join();
        }
    }
}

void ReceiveProcess::ListenWorker()
{
    SOCKET sock;
    m_listener.Listen(12345, 5);
    while(m_isRunning)
    {
        sock = m_listener.Accept();
        if(sock == NULL)
        {
            std::cout << "accept error" << std::endl;
            continue;
        }
        std::cout << "accept" << std::endl;
        m_recvThreads.push_back(std::thread(&ReceiveProcess::RecvWorker, this, sock));
        if(m_recvThreads.size() >= m_maxClientNum)
        {
            std::cout << "max client num" << std::endl;
            break;
        }
    }
}

void ReceiveProcess::RecvWorker(SOCKET sock)
{
    TcpReceiver receiver(sock);
    std::vector<char> buf(1024);

    while(m_isRunning)
    {
        if(receiver.Receive(buf) == false)
        {
            std::cout << "recv error" << std::endl;
            break;
        }

        // analyze received data

    }
}


std::string GetSerialNo(std::vector<char> buf)
{
    // analyze received data
    // get serial no from received data
    // serial no is 16 bytes in received data from 0 byte

    std::string serialNo;
    for(int i = 0; i < 16; i++)
    {
        serialNo += buf[i];
    }

    return serialNo;
}

// void AddClient(std::string serialNo, TcpReceiver client)
// {
//     // add client to clientList
//     ClientInfo clientInfo;
//     clientInfo.sock = client;
//     clientInfo.ip = "";
//     g_clientList[serialNo] = clientInfo;
// }

// void RemoveClient(std::string serialNo)
// {
//     // remove client from clientList

//     g_clientList.erase(serialNo);
// }