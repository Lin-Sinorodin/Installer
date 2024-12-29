#ifndef INSTALLER_INSTALLER_H
#define INSTALLER_INSTALLER_H

#include <string>
#include <vector>

// Installer class that installs files from a source directory to a destination directory.
class Installer
{
private:
    std::string src_dir;
    std::string dst_dir;
    std::vector<std::string> file_names;

    // Get full file path from directory path and file name.
    std::string getFilePath(const std::string &dir_path, const std::string &file_name);

    // Core function that handles the installation logic.
    void _install();

public:
    Installer(const std::string &src_dir, const std::string &dst_dir,
              const std::vector<std::string> &file_names);

    void install();
};

#endif // INSTALLER_INSTALLER_H
