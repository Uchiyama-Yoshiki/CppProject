#include <windows.h>
#include <string>
#include <stdexcept>
#include <iostream>
#include <vector>
#include "BufferStructure.h"

struct BufferStruct
{
    int serial;
    int id;
    int ch;
    int record;
    int size;
    int write;
    int read;
    int end;
    int start;
    int flag;
    int status;
    int error;
    int reserve[20];
};

/**
 * @brief DataBufferAccessor class
 * @details This class is a data buffer class that is accessed by two processes.
 * One is the process of writing data.
 * One is the process of reading data.  
 * The data to be written is stored in a ring buffer in shared memory.
 * The data to be read is read from the ring buffer in shared memory.
 * The ring buffer is a circular buffer.
 * One record of data consists of time data and CH data.
 * The CH data is 8 bytes, and the maximum number of CHs is 32CH.
 * The buffer structure is stored in shared memory in BufferStructuer class.
 * The data is stored in shared memory in DataBuffer class.
 */
class DataBufferAccessor
{
private:
DataBuffer *pBuf;
BufferStructure*pBufStruct;


public:
    /**
     * @brief Constructor
     */
    DataBufferAccessor();

    /**
     * @brief Destructor
     */
    ~DataBufferAccessor();

    /**
     * @brief Register buffer structure in shared memory
     * @param[in] serial number
     * @param[in] id
     * @param[in] buffer structure
     */
    void RegisterBufferStructure(int serial, int id, BufferStructure &bufStruct);

    /**
     * @brief Write data to the ring buffer in shared memory
     * @param[in] number of CHs
     * @param[in] number of records
     */
    void WriteData(LPVOID data, int ch, int record);
};