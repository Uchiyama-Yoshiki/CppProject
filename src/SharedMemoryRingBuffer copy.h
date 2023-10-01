#include <windows.h>
#include <string>
#include <stdexcept>

class SharedMemoryRingBuffer {
private:
    HANDLE hMapFile;
    LPVOID pBuf;
    size_t size;
    size_t readIndex;
    size_t writeIndex;
    std::string name;

    void incrementIndex(size_t& index);
    void decrementIndex(size_t& index);
    void* getPointer(size_t index);
    void* getPointer(size_t index, size_t offset);
    void* getReadPointer();
    void* getWritePointer();
    size_t getReadIndex();
    size_t getWriteIndex();
    size_t getReadAvailable();
    size_t getWriteAvailable();
    size_t getReadAvailable(size_t readIndex, size_t writeIndex);
    size_t getWriteAvailable(size_t readIndex, size_t writeIndex);
    size_t getReadAvailable(size_t readIndex, size_t writeIndex, size_t size);
    size_t getWriteAvailable(size_t readIndex, size_t writeIndex, size_t size);
    size_t getReadAvailable(size_t size);
    size_t getWriteAvailable(size_t size);
    size_t getReadAvailable(size_t readIndex, size_t writeIndex, size_t size, size_t maxSize);
    size_t getWriteAvailable(size_t readIndex, size_t writeIndex, size_t size, size_t maxSize);
    size_t getReadAvailable(size_t size, size_t maxSize);
    size_t getWriteAvailable(size_t size, size_t maxSize);
    void write(const void* data, size_t size, size_t& index);
    void read(void* data, size_t size, size_t& index);
    void write(const void* data, size_t size, size_t& index, size_t& readIndex, size_t& writeIndex);
    void read(void* data, size_t size, size_t& index, size_t& readIndex, size_t& writeIndex);
    void write(const void* data, size_t size, size_t& index, size_t& readIndex, size_t& writeIndex, size_t maxSize);
    void read(void* data, size_t size, size_t& index, size_t& readIndex, size_t& writeIndex, size_t maxSize);
    void write(const void* data, size_t size, size_t& index, size_t& readIndex, size_t& writeIndex, size_t maxSize, size_t& readAvailable, size_t& writeAvailable);
    void read(void* data, size_t size, size_t& index, size_t& readIndex, size_t& writeIndex, size_t maxSize, size_t& readAvailable, size_t& writeAvailable);
public:
    SharedMemoryRingBuffer(const std::string& name, size_t size);
    ~SharedMemoryRingBuffer();

    void write(const void* data, size_t size);
    void read(void* data, size_t size);
};