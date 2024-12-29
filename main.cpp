#include "installer.h"

int main()
{
    const std::string src_dir = R"(C:\\Users\\psagot1\\CLionProjects\\lin_installer\\demo\src)";
    const std::string dst_dir = R"(C:\\Users\\psagot1\\CLionProjects\\lin_installer\\demo\dst)";
    Installer installer(src_dir, dst_dir, {"file1.txt", "file2.txt", "file3.txt"});
    installer.install();

    return 0;
}
