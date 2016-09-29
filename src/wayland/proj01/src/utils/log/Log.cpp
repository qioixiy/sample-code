#include <ctime>
#include <sys/time.h>
#include <iostream>
#include <fstream>
#include "Log.hpp"

LoggerStream::LoggerStream()
  : stream(new Stream()) {}

LoggerStream::LoggerStream(std::string *s)
  : stream(new Stream(s)) {}

LoggerStream::~LoggerStream()
{
  toConsole(stream->loggerType, stream->context, stream->ss.str());
  delete stream;
}

void LoggerStream::mkTimeSpec(std::ostringstream& ss)
{
#define MST (-7)
#define UTC (0)
#define CCT (+8)
  struct timeval tv;
  gettimeofday(&tv, NULL);
  struct tm * ptm = gmtime(&tv.tv_sec);
  //ss << tv.tv_sec << ':' << tv.tv_usec << ' ';
  ss << 1900+ptm->tm_year << '-'
     << ptm->tm_mon << '-'
     << ptm->tm_mday << ' ' ;
  ss << (ptm->tm_hour+CCT)%24 << ':'
     << ptm->tm_min << ':'
     << ptm->tm_sec << ':'
     << tv.tv_usec << ' ';
}

void LoggerStream::toConsole(LoggerType type,
                             const LoggerContext &context,
                             std::string logBuffer)
{
  std::ostringstream ss;
  switch (type) {
  default:
  case E_Debug: ss << "D:"; break;
  case E_Info: ss << "I:"; break;
  case E_Warning: ss << "W:"; break;
  case E_Critical:ss << "C:"; break;
  case E_Error: ss << "E:"; break;
  }

  mkTimeSpec(ss);
  ss << context.file
     << " L:" << context.line
     << " " << context.function << "()"
     << " " << logBuffer;

  std::cout << ss.str() << std::endl;
}

LoggerStream Logger::Debug() const
{
  LoggerStream ls = LoggerStream();
  LoggerContext &ctxt = ls.stream->context;
  ctxt.copy(context);
  ls.stream->loggerType = E_Debug;
  return ls;
}

LoggerStream Logger::Info() const
{
  LoggerStream ls;
  LoggerContext &ctxt = ls.stream->context;
  ctxt.copy(context);
  ls.stream->loggerType = E_Info;
  return ls;
}

LoggerStream Logger::Warning() const
{
  LoggerStream ls;
  LoggerContext &ctxt = ls.stream->context;
  ctxt.copy(context);
  ls.stream->loggerType = E_Warning;
  return ls;
}

LoggerStream Logger::Critical() const
{
  LoggerStream ls;
  LoggerContext &ctxt = ls.stream->context;
  ctxt.copy(context);
  ls.stream->loggerType = E_Critical;
  return ls;
}

LoggerStream Logger::Error() const
{
  LoggerStream ls;
  LoggerContext &ctxt = ls.stream->context;
  ctxt.copy(context);
  ls.stream->loggerType = E_Error;
  return ls;
}
