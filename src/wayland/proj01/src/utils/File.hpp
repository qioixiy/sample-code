#ifndef _FILE_H_
#define _FILE_H_

#include <string>

using namespace std;

class File {
public:
  File(string filePath);
  string& GetStringData();

private:
  string strData;
};

#endif
