#include <iostream>
#include <stdexcept>
#include <windows.h>
#include "directory.h"

bool directoryExists(const std::string &path)
{
    DWORD attributes = GetFileAttributes(path.c_str());
    bool is_valid = attributes != INVALID_FILE_ATTRIBUTES;
    bool is_directory = attributes & FILE_ATTRIBUTE_DIRECTORY;
    return is_valid && is_directory;
}

Directory::Directory(const std::string &path) : path(path), keep(true) {}
Directory::Directory(const std::string &path, bool keep) : path(path), keep(keep) {}

Directory::~Directory()
{
    if (!keep && exists())
    {
        remove();
    }
}

bool Directory::exists()
{
    return directoryExists(path);
}

void Directory::remove()
{
    if (exists())
    {
        if (!RemoveDirectory(path.c_str()))
        {
            throw std::runtime_error("Failed to remove directory: " + path);
        }
    }
    std::cout << "[-] Removed directory: \n\t" << path << std::endl;
}

void Directory::create()
{
    if (!CreateDirectory(path.c_str(), NULL))
    {
        throw std::runtime_error("Failed to create directory: " + path);
    }
    std::cout << "[+] Created directory: \n\t" << path << std::endl;
}

void Directory::setKeep(bool new_keep)
{
    keep = new_keep;
}

std::string Directory::getPath()
{
    return path;
}
