#include "BufferStructure.h"

BufferStructure::BufferStructure() : hMapFile(NULL),
                                     pBuf(NULL)
{
}

BufferStructure::~BufferStructure()
{
    Close();
}

void BufferStructure::Create(std::string name)
{
    // name convert LPCTSTR
    LPCTSTR lpName = (LPCTSTR)name.c_str();

    hMapFile = CreateFileMapping(
        INVALID_HANDLE_VALUE,
        NULL,
        PAGE_READWRITE,
        0,
        sizeof(BufferStructure),
        lpName);

    if (hMapFile == NULL)
    {
        throw std::runtime_error("CreateFileMapping failed.");
    }
    // Already exist
    if (GetLastError() == ERROR_ALREADY_EXISTS)
    {
        throw std::runtime_error("ERROR_ALREADY_EXISTS.");
    }

    pBuf = MapViewOfFile(
        hMapFile,
        FILE_MAP_ALL_ACCESS,
        0,
        0,
        sizeof(BufferStructure));

    if (pBuf == NULL)
    {
        throw std::runtime_error("MapViewOfFile failed.");
    }
}

void BufferStructure::Open(std::string name)
{
    // name convert LPCTSTR
    LPCTSTR lpName = (LPCTSTR)name.c_str();

    hMapFile = OpenFileMapping(
        FILE_MAP_ALL_ACCESS,
        FALSE,
        lpName);

    if (hMapFile == NULL)
    {
        throw std::runtime_error("OpenFileMapping failed.");
    }

    pBuf = MapViewOfFile(
        hMapFile,
        FILE_MAP_ALL_ACCESS,
        0,
        0,
        sizeof(BufferStructure));

    if (pBuf == NULL)
    {
        throw std::runtime_error("MapViewOfFile failed.");
    }
}

void BufferStructure::Close()
{
    if (pBuf != NULL)
    {
        UnmapViewOfFile(pBuf);
        pBuf = NULL;
    }

    if (hMapFile != NULL)
    {
        CloseHandle(hMapFile);
        hMapFile = NULL;
    }
}

void BufferStructure::Write(BufferStructure bufferStructure)
{
    if (pBuf != NULL)
    {
        memcpy_s(pBuf, sizeof(BufferStructure), &bufferStructure, sizeof(BufferStructure));
    }
    else
    {
        throw std::runtime_error("pBuf is NULL.");
    }
}

BufferStructure BufferStructure::Read()
{
    BufferStructure bufferStructure;
    if (pBuf != NULL)
    {
        memcpy_s(&bufferStructure, sizeof(BufferStructure), pBuf, sizeof(BufferStructure));
    }
    else
    {
        throw std::runtime_error("pBuf is NULL.");
    }
    return bufferStructure;
}