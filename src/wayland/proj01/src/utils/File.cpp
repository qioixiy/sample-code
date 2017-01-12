#include <fstream>
#include <sstream>
#include "File.hpp"
#include "utils/log/Log.hpp"

using namespace std;

File::File(string filePath)
    : filePath(filePath)
    , bytes(NULL)
{
    ;
}

File::~File()
{
    if (bytes) {
        delete bytes;
    }
}

string&
File::GetStringData()
{
  if (strData.empty()) {
    ifstream in(filePath);
    if (! in.is_open()) {
        LogE << "open file" << filePath << "error";
    }

    char ch;
    stringstream ss;
    while (!in.eof()) {
        in.get(ch);
        ss << ch;
    }
    strData = ss.str();
  }

  return strData;
}

char*
File::GetBytes()
{
    if (!bytes) {
        ifstream in(filePath, ios::binary);
        streampos pos = in.tellg(); // save current position
        in.seekg(0, ios::end);
        int size = in.tellg();
        in.seekg(pos); // restore saved position
        bytes = new char[size];
        in.read(bytes, size);
    }

    return bytes;
}
