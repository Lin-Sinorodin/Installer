#ifndef INSTALLER_FILE_H
#define INSTALLER_FILE_H

#include <string>

bool fileExists(const std::string &path);

// File class that represents a file in the file system.
class File
{
private:
    std::string path;
    bool keep;

public:
    explicit File(const std::string &path); // keep is true by default.
    File(const std::string &path, bool keep);
    ~File(); // RAII - remove the file if it exists and keep is false.

    bool exists();
    void remove();
    void copy(const std::string &dst);
    void setKeep(bool new_keep);
    std::string getPath();
};

#endif // INSTALLER_FILE_H
