#include <Windows.h>
#include <cstdio>
#include <iostream>
// #include "ReceiveProcess.h"

// std::map<std::string,ClientInfo> g_clientList;
// std::vector<ClientInfo> g_clientList;
// struct ClientInfo
// {
//     TcpReceiver sock;
//     std::string ip;
// };

int main(int argc, char *argv[])
{

    // std::cout << "start" << std::endl;
    // int port = 12345;
    // int maxClientNum = 5;
    // ReceiveProcess receiveProcess(port,maxClientNum);

    // while(true)
    // {
    //     std::this_thread::sleep_for(std::chrono::seconds(1));
    //     // input  "q" to quit
    //     if(getchar() == 'q')
    //     {
    //         break;
    //     }
    // }
    printf("start\n");
    // std::cout << "end" << std::endl;
    // system("pause");
    return 0;
}

// void EndApp()
// {
//     // listener close
//     g_listener.Close();
//     // clientList close
//     for(auto client : g_clientList)
//     {
//         client.sock.Close();
//     }
// }

// void listenThread()
// {
//     SOCKET sock;

//     g_listener.Listen(12345);
//     while(true)
//     {
//         sock = g_listener.Accept();
//         if(sock == NULL)
//         {
//             std::cout << "accept error" << std::endl;
//             continue;
//         }
//         std::cout << "accept" << std::endl;
//         // g_socks.emplace_back(new TcpReceiver(sock));
//         std::thread recv(recvThread, sock);
//     }
// }

// void recvThread(SOCKET sock)
// {
//     TcpReceiver receiver(sock);
//     std::vector<char> buf(1024);

//     while(true)
//     {
//         if(receiver.Receive(buf) == false)
//         {
//             std::cout << "recv error" << std::endl;
//             // remove TcpReceiver from clientList
//             RemoveClient(serialNo);
//             break;
//         }
//         std::cout << "recv" << std::endl;

//         // check serial no in received data
//         // if not exist in clientList, add to clientList
//         // If present in clientList, the connection does nothing as a reconnection.
//         std::string serialNo = GetSerialNo(buf);
//         if(ExistClient(serialNo) == false)
//         {
//             AddClient(serialNo, receiver);
//         }

//         // analyze received data

//         // analyzed data is write to memory


//     }
// }