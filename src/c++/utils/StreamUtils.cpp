#include <iostream>
#include <fstream>
#include "StreamUtils.hpp"

int StreamUtils::fileSize(std::string path)
{
    return std::ifstream(
        path, std::ios_base::binary).seekg(0, std::ios_base::end).tellg();
}

int StreamUtils::copyFile(std::string src, std::string dest)
{
    std::ifstream input(src, std::ios::binary);
    std::ofstream output(dest, std::ios::binary);
    output << input.rdbuf();

    return 0;
}

int StreamUtils::saveFile(std::string path, const char* buf, size_t size)
{
    std::ofstream out(path);
    out.write(buf, size);

    return size;
}
