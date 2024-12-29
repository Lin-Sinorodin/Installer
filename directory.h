#ifndef INSTALLER_DIRECTORY_H
#define INSTALLER_DIRECTORY_H

#include <string>

bool directoryExists(const std::string &path);

// Directory class that represents a directory in the file system.
class Directory
{
private:
    std::string path;
    bool keep;

public:
    explicit Directory(const std::string &path); // keep is true by default.
    Directory(const std::string &path, bool keep);
    ~Directory(); // RAII - remove the directory if it exists and keep is false.

    bool exists();
    void remove();
    void create();
    void setKeep(bool new_keep);
    std::string getPath();
};

#endif // INSTALLER_DIRECTORY_H
