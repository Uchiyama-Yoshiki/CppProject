#include <windows.h>
#include <string>
#include <stdexcept>

typedef struct {
    int readIndex;
    int writeIndex;
    int chNum;
    size_t dataBufferSize;
} BufferStructure;

/**
 * @brief BufferStructure class
 * @details This class is a buffer structure class.
 * DataBuffer class stores data in shared memory.
 * BufferStructure class stores buffer structure in shared memory.
 * Created and deleted by read process.
 */
class BufferStructure
{
private:
HANDLE hMapFile;
LPVOID pBuf;

public:
    /**
     * @brief BufferStructure constructor
     *
     */
    BufferStructure();
    /**
     * @brief BufferStructure destructor
     *
     */
    ~BufferStructure();

    /**
     * @brief create shared memory
     * @details This function creates shared memory.
     * @param[in] shared memory name
     */
    void Create(std::string name);

    /**
     * @brief open shared memory
     *
     * @param[in] shared memory name
     */
    void Open(std::string name);

    /**
     * @brief close shared memory
     *
     */
    void Close();

    /**
     * @brief write buffer structure
     * @details This function writes buffer structure.
     * @param[in] buffer structure
     */
    void Write(BufferStructure bufferStructure);

    /**
     * @brief read buffer structure
     * @details This function reads buffer structure.
     * @return buffer structure
     */
    BufferStructure Read();
};