#pragma once

#include <string>

class StreamUtils {
public:
    static int fileSize(std::string path);
    static int copyFile(std::string src, std::string dest);
    static int saveFile(std::string path, const char* buf, size_t size);
};
