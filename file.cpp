#include <iostream>
#include <stdexcept>
#include <windows.h>
#include "file.h"

bool fileExists(const std::string &path)
{
    DWORD attributes = GetFileAttributes(path.c_str());
    bool is_valid = attributes != INVALID_FILE_ATTRIBUTES;
    bool is_file = !(attributes & FILE_ATTRIBUTE_DIRECTORY);
    return is_valid && is_file;
}

File::File(const std::string &path) : path(path), keep(true) {}
File::File(const std::string &path, bool keep) : path(path), keep(keep) {}

File::~File()
{
    if (!keep & exists())
    {
        remove();
    }
}

bool File::exists()
{
    return fileExists(path);
}

void File::remove()
{
    if (exists())
    {
        if (!DeleteFile(path.c_str()))
        {
            throw std::runtime_error("Failed to remove file: " + path);
        }
    }
    std::cout << "[-] Removed file: \n\t" << path << std::endl;
}

void File::copy(const std::string &dst)
{
    if (!CopyFile(path.c_str(), dst.c_str(), FALSE))
    {
        throw std::runtime_error("Failed to copy file: " + path);
    }
    std::cout << "[+] Copied file: \n\tFrom: " << path << "\n\tTo:   " << dst << std::endl;
}

void File::setKeep(bool new_keep)
{
    keep = new_keep;
}

std::string File::getPath()
{
    return path;
}
