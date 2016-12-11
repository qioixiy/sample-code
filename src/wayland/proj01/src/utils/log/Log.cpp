#include <ctime>
#include <sys/time.h>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <map>
#include <iomanip>
#include "Log.hpp"

#define ANSI_RED(fmt) ("\x1b[31m" fmt "\x1b[0m")
#define ANSI_GREEN(fmt) ("\x1b[32m" fmt "\x1b[0m")
#define ANSI_BROWN(fmt) ("\x1b[33m" fmt "\x1b[0m")
#define ANSI_BLUE(fmt) ("\x1b[33m" fmt "\x1b[0m")

#define _ANSI_RED "\x1b[31m"
#define _ANSI_HIGHBRIGHTNESS_RED "\x1b[1;31m"
#define _ANSI_GREEN "\x1b[32m"
#define _ANSI_BROWN "\x1b[33m"
#define _ANSI_BLUE "\x1b[34m"

#define ANSI_RESET "\x1b[0m"

#ifdef USE_LOG_CAT
#include <base/log/Log.h>
#endif

#ifdef USE_LOG_CAT
bool LoggerStream::useLogCat = true;
#endif
std::string LoggerStream::TAG = "";

LoggerStream::LoggerStream()
  : stream(new Stream()) {}

LoggerStream::LoggerStream(std::string *s)
  : stream(new Stream(s)) {}

LoggerStream::~LoggerStream()
{
  std::ostringstream sstimestamp;
  mkTimeSpec0(sstimestamp);

  toConsole(stream->loggerType, stream->context,
            stream->ss.str(), sstimestamp);
#ifdef USE_LOG_CAT
  if (useLogCat) {
    toLogCat(stream->loggerType, stream->context,
             stream->ss.str(), sstimestamp);
  }
#endif
  delete stream;
}

void
LoggerStream::mkTag(std::ostringstream& ss)
{
  ss << TAG;
}

void
LoggerStream::mkTimeSpec0(std::ostringstream& ss)
{
  char buf[40]="";
#define USEC_TO_SEC(usec) (usec/1000000.0)
  struct timeval current;
  double time;
  gettimeofday(&current, NULL);
  time = current.tv_sec + USEC_TO_SEC(current.tv_usec);
  sprintf(buf, "[%lf]", time);
  ss << buf;
}
void
LoggerStream::mkTimeSpec1(std::ostringstream& ss)
{
#define MST (-7)
#define UTC (0)
#define CCT (+8)
  struct timeval tv;
  gettimeofday(&tv, NULL);
  struct tm * ptm = gmtime(&tv.tv_sec);

  ss << '[';
  ss << 1900+ptm->tm_year << '-'
     << std::setw(2) << std::setfill('0') << 1+ptm->tm_mon << '-'
     << std::setw(2) << std::setfill('0') << ptm->tm_mday << ' ' ;
  ss << std::setw(2) << std::setfill('0') << (ptm->tm_hour+CCT)%24 << ':'
     << std::setw(2) << std::setfill('0') << ptm->tm_min << ':'
     << std::setw(2) << std::setfill('0') << ptm->tm_sec << ':'
     << std::setw(6) << std::setfill('0') << tv.tv_usec << std::setw(0);
  ss << ']';
}

const char*
LoggerStream::mkType(LoggerType type,
                     const LoggerContext &context,
                     std::ostringstream& ss)
{
  const char* ret = "";
  ss << "[";
  switch (type) {
  default:
  case E_Debug: ss << "D"; break;
  case E_Info: ss << "I"; ret = _ANSI_BLUE; break;
  case E_Warning: ss << "W"; ret = _ANSI_BROWN; break;
  case E_Critical:ss << "C"; ret = _ANSI_HIGHBRIGHTNESS_RED; break;
  case E_Error: ss << "E"; ret = _ANSI_RED; break;
  }
  ss << "]";

  return ret;
}

class map_finder
{
public:
  map_finder(const char* _s):str(_s){}
  bool operator ()(const std::map<const char*, int>::value_type &pair){
    return pair.first == str;
  }
private:
  const char* str;
};
static const char* skipFilePathDir(const char* s)
{
  std::map<const char*, int> mapFiles;
  const std::map<const char*, int>::iterator iter
    = std::find_if(mapFiles.begin(), mapFiles.end(), map_finder(s));
  if (iter == mapFiles.end()) {
    mapFiles[s] = 1+std::string(s).rfind('/');
    return s+mapFiles[s];
  }
  return &s[iter->second];
}
void
LoggerStream::mkBannaer(LoggerType type,
                        const LoggerContext &context,
                        std::ostringstream& ss)
{
  // " funtion,file+Lno: "
  ss << " " << context.function << ","
     << skipFilePathDir(context.file)
     << "+L" << context.line << ": ";
}

void
LoggerStream::toConsole(LoggerType type,
                        const LoggerContext &context,
                        const std::string &logBuffer,
                        const std::ostringstream &sstimestamp)
{
  std::ostringstream ss;

  ss << _ANSI_GREEN << sstimestamp.str() << ANSI_RESET;
  ss << _ANSI_BROWN;
  mkTag(ss);
  ss << ANSI_RESET;
  const char* color = mkType(type, context, ss);
  mkBannaer(type, context, ss);

  ss << color << logBuffer << ANSI_RESET;

  switch (type) {
  default:
  case E_Debug:
  case E_Info:
    std::cout << ss.str() << std::endl; break;
  case E_Warning:
  case E_Critical:
  case E_Error:
    std::cerr << ss.str() << std::endl; break;
  }
}

#ifdef USE_LOG_CAT
void
LoggerStream::toLogCat(LoggerType type,
                       const LoggerContext &context,
                       const std::string &logBuffer,
                       const std::ostringstream &sstimestamp)
{

#ifndef LOG_TAG
#define LOG_TAG "SRV"
#endif

  std::ostringstream ss;

  ss << sstimestamp.str();
  mkBannaer(type, context, ss);
  ss << logBuffer;

  switch (type) {
  default:
  case E_Debug: LOG_D("%s", ss.str().c_str()); break;
  case E_Info: LOG_I("%s", ss.str().c_str()); break;
  case E_Warning: LOG_W("%s", ss.str().c_str()); break;
  case E_Critical: LOG_E("%s", ss.str().c_str()); break;
  case E_Error: LOG_E("%s", ss.str().c_str()); break;
  }
}
#endif

LoggerStream Logger::__xxDebug() const
{
  return genLoggerStream(E_Debug);
}

LoggerStream Logger::__xxInfo() const
{
  return genLoggerStream(E_Info);
}

LoggerStream Logger::__xxWarning() const
{
  return genLoggerStream(E_Warning);
}

LoggerStream Logger::__xxCritical() const
{
  return genLoggerStream(E_Critical);
}

LoggerStream Logger::__xxError() const
{
  return genLoggerStream(E_Error);
}

LoggerStream Logger::genLoggerStream(enum LoggerType type) const
{
  LoggerStream ls;
  LoggerContext &ctxt = ls.stream->context;
  ctxt.copy(context);
  ls.stream->loggerType = type;
  return ls;
}
