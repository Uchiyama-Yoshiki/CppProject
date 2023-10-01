#include <WinSock2.h>
#include <thread>

/**
 * @brief 
 * @details 
 * This class accepts multiple TCP clients.
 * All communication with devices is asynchronous.
 * The library is Winsock.
 * The connection is assumed to be always connected.
 * After connection, two types of communication data will be received.
 * The first is normal data.
 * Normal data is sent by the client as needed.
 * The second is line monitoring data.
 * Data that the client sends when it would not normally send data.
 * The data received from the client.
 * The received data is passed to the analysis output process asynchronously.
 */
class TcpServer
{
private:
    int m_port;
    SOCKET m_sock;
    std::thread m_thread;
    int m_clientCount;

    /**
     * @brief Thread function
     */
    void Thread();

    /**
     * @brief Accept function
     */
    void Accept();

    /**
     * @brief Receive function
     * @param[in] client socket
     */
    void Receive(SOCKET client);

    /**
     * @brief Send function
     * @param[in] client socket
     * @param[in] data
     * @param[in] size
     */
    void Send(SOCKET client, char *data, int size);
public:
    /**
     * @brief Constructor
     */
    TcpServer();

    /**
     * @brief Destructor
     */
    ~TcpServer();

    /**
     * @brief Start TCP Server
     * @details
     * mutiple clients can connect to the server.
     * another thread is created for each client.
     * 
     * @param[in] port number
     * @return int
     */
    int Start(int port);

    /**
     * @brief Stop TCP Server
     * @return int
     */
    int Stop();

    /**
     * @brief Get the number of clients
     * @return int
     */
    int GetClientCount();
};