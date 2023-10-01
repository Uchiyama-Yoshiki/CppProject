#include "SharedMemoryRingBuffer.h"

SharedMemoryRingBuffer::SharedMemoryRingBuffer(const std::string &name, size_t size)
{
    this->name = name;
    this->size = size;
    this->readIndex = 0;
    this->writeIndex = 0;

    hMapFile = CreateFileMappingA(
        INVALID_HANDLE_VALUE, // use paging file
        NULL,                 // default security
        PAGE_READWRITE,       // read/write access
        0,                    // maximum object size (high-order DWORD)
        size,                 // maximum object size (low-order DWORD)
        name.c_str());        // name of mapping object

    if (hMapFile == NULL)
    {
        throw std::runtime_error("Could not create file mapping object");
    }

    pBuf = MapViewOfFile(hMapFile,            // handle to map object
                         FILE_MAP_ALL_ACCESS, // read/write permission
                         0,
                         0,
                         size);

    if (pBuf == NULL)
    {
        CloseHandle(hMapFile);
        throw std::runtime_error("Could not map view of file");
    }
}

SharedMemoryRingBuffer::~SharedMemoryRingBuffer()
{
    UnmapViewOfFile(pBuf);
    CloseHandle(hMapFile);
}

void SharedMemoryRingBuffer::incrementIndex(size_t &index)
{
    index++;
    if (index >= size)
    {
        index = 0;
    }
}

void SharedMemoryRingBuffer::decrementIndex(size_t &index)
{
    if (index == 0)
    {
        index = size - 1;
    }
    else
    {
        index--;
    }
}

void *SharedMemoryRingBuffer::getPointer(size_t index)
{
    return getPointer(index, 0);
}

void *SharedMemoryRingBuffer::getPointer(size_t index, size_t offset)
{
    return (void *)((char *)pBuf + index + offset);
}

void *SharedMemoryRingBuffer::getReadPointer()
{
    return getPointer(readIndex);
}

void *SharedMemoryRingBuffer::getWritePointer()
{
    return getPointer(writeIndex);
}

size_t SharedMemoryRingBuffer::getReadIndex()
{
    return readIndex;
}

size_t SharedMemoryRingBuffer::getWriteIndex()
{
    return writeIndex;
}

size_t SharedMemoryRingBuffer::getReadAvailable()
{
    return getReadAvailable(readIndex, writeIndex);
}

size_t SharedMemoryRingBuffer::getWriteAvailable()
{
    return getWriteAvailable(readIndex, writeIndex);
}

size_t SharedMemoryRingBuffer::getReadAvailable(size_t readIndex, size_t writeIndex)
{
    return getReadAvailable(readIndex, writeIndex, size);
}

size_t SharedMemoryRingBuffer::getWriteAvailable(size_t readIndex, size_t writeIndex)
{
    return getWriteAvailable(readIndex, writeIndex, size);
}

size_t SharedMemoryRingBuffer::getReadAvailable(size_t readIndex, size_t writeIndex, size_t size)
{
    return getReadAvailable(readIndex, writeIndex, size, this->size);
}

size_t SharedMemoryRingBuffer::getWriteAvailable(size_t readIndex, size_t writeIndex, size_t size)
{
    return getWriteAvailable(readIndex, writeIndex, size, this->size);
}

size_t SharedMemoryRingBuffer::getReadAvailable(size_t readIndex, size_t writeIndex, size_t size, size_t maxSize)
{
    if (readIndex == writeIndex)
    {
        return maxSize;
    }
    else if (readIndex < writeIndex)
    {
        return writeIndex - readIndex;
    }
    else
    {
        return maxSize - readIndex + writeIndex;
    }
}

size_t SharedMemoryRingBuffer::getWriteAvailable(size_t readIndex, size_t writeIndex, size_t size, size_t maxSize)
{
    if (readIndex == writeIndex)
    {
        return maxSize;
    }
    else if (readIndex < writeIndex)
    {
        return maxSize - writeIndex + readIndex;
    }
    else
    {
        return readIndex - writeIndex;
    }
}
void SharedMemoryRingBuffer::write(const void *data, size_t size, size_t &index)
{
    write(data, size, index, readIndex, writeIndex);
}
void SharedMemoryRingBuffer::read(void *data, size_t size, size_t &index)
{
    read(data, size, index, readIndex, writeIndex);
}
void SharedMemoryRingBuffer::write(const void *data, size_t size, size_t &index, size_t &readIndex, size_t &writeIndex)
{
    write(data, size, index, readIndex, writeIndex, this->size);
}
void SharedMemoryRingBuffer::read(void *data, size_t size, size_t &index, size_t &readIndex, size_t &writeIndex);
void SharedMemoryRingBuffer::write(const void *data, size_t size, size_t &index, size_t &readIndex, size_t &writeIndex, size_t maxSize);
void SharedMemoryRingBuffer::read(void *data, size_t size, size_t &index, size_t &readIndex, size_t &writeIndex, size_t maxSize);
void SharedMemoryRingBuffer::write(const void *data, size_t size, size_t &index, size_t &readIndex, size_t &writeIndex, size_t maxSize, size_t &readAvailable, size_t &writeAvailable);
void SharedMemoryRingBuffer::read(void *data, size_t size, size_t &index, size_t &readIndex, size_t &writeIndex, size_t maxSize, size_t &readAvailable, size_t &writeAvailable)
{
    if (size > maxSize)
    {
        throw std::runtime_error("Size is larger than maximum size");
    }

    if (size > writeAvailable)
    {
        throw std::runtime_error("Not enough space to write");
    }

    memcpy(getPointer(index), data, size);
    incrementIndex(index);
    writeAvailable -= size;


void SharedMemoryRingBuffer::write(const void *data, size_t size)
{
    write(data, size, writeIndex);
}

void SharedMemoryRingBuffer::read(void *data, size_t size)
{
    read(data, size, readIndex);
}