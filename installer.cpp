#include <iostream>
#include <stdexcept>
#include <memory>
#include "installer.h"
#include "directory.h"
#include "file.h"

Installer::Installer(const std::string &src_dir, const std::string &dst_dir,
                     const std::vector<std::string> &file_names) : src_dir(src_dir), dst_dir(dst_dir), file_names(file_names)
{
    if (!directoryExists(src_dir))
    {
        throw std::runtime_error("Source directory is missing.");
    }
}

std::string Installer::getFilePath(const std::string &dir_path, const std::string &file_name)
{
    std::string file_path = dir_path;
    if (!dir_path.empty() && dir_path.back() != L'\\')
    {
        file_path += L'\\';
    }
    file_path += file_name;
    return file_path;
}

/* Note about how RAII works in case of deleting created directory (rollback if failed):
    Objects are destroyed in the reverse order of their construction.
    Therefore, dst_files are destroyed (and the files are removed) before dst is destroyed (and the directory is removed).
    This way, the directory ensured to be empty before it is removed (according to WinAPI restrictions).
 */
void Installer::_install()
{
    // Check if destination directory exists, if not create it.
    Directory dst(dst_dir);
    if (!dst.exists())
    {
        dst.create();
        dst.setKeep(false);
    }

    // Initialize a vector of created files, with keep=false.
    std::vector<std::shared_ptr<File>> dst_files;
    for (const std::string &file_name : file_names)
    {
        // Initialize source file and ensure it's exists.
        std::string src_file_path = getFilePath(src_dir, file_name);
        File src_file(src_file_path);
        if (!src_file.exists())
        {
            throw std::runtime_error("Missing file: " + file_name);
        }

        // Copy file and create new file object with default to not keep it.
        std::string dst_file_path = getFilePath(dst.getPath(), file_name);
        src_file.copy(dst_file_path);
        auto dst_file = std::make_shared<File>(dst_file_path, false);
        dst_files.push_back(dst_file);
    }

    // If the code arrives here - copy was successfull. Ensure new files are kept.
    dst.setKeep(true);
    for (const auto &file : dst_files)
    {
        file->setKeep(true);
    }

}

void Installer::install()
{
    std::cout << "Welcome to Installer!" << std::endl;
    std::cout << "Copying files..." << std::endl;
    try
    {
        _install();
    }
    catch (std::exception &e)
    {
        std::cout << "[!] Error occurred: \n\t" << e.what() << std::endl;
        std::cout << "Rolling back changes..." << std::endl;
    }
    std::cout << "Done!" << std::endl;
}
