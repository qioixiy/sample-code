#ifndef _FILE_H_
#define _FILE_H_

#include <string>

using namespace std;

class File
{
public:
    File(string filePath);
    virtual ~File();

    string &GetStringData();
    char *GetBytes();

private:
    string filePath;

    string strData;
    char *bytes;
};

#endif
