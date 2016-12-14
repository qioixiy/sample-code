#include <fstream>
#include <sstream>
#include "File.hpp"
#include "utils/log/Log.hpp"

using namespace std;

File::File(string filePath)
{
  ifstream in(filePath);
  if (! in.is_open()) {
    LogE << "open file" << filePath << "error";
    return;
  }

  char ch;
  stringstream ss;
  while (!in.eof()) {
    in.get(ch);
    ss << ch;
  }
  strData = ss.str();
}

string&
File::GetStringData()
{
  return strData;
}
