#pragma once

#include <string>
#include <sstream>

enum LoggerType
{
  E_Debug = 0,
  E_Info,
  E_Warning,
  E_Critical,
  E_Error,
  E_Default = E_Debug,
};

class LoggerContext
{
  friend class Logger;
  friend class LoggerStream;

public:
  LoggerContext(const char *_file="",
                const char *_function="",
                int _line = -1)
    : line(_line), file(_file), function(_function) {}

  void copy(const LoggerContext &cxt) {
    file = cxt.file;
    line = cxt.line;
    function = cxt.function;
  }

private:
  int line;
  const char *file;
  const char *function;
};

class LoggerStream
{
public:
  struct Stream {
    Stream():ss(), space(true), context() {}
    Stream(std::string *s)
      :ss(*s, std::ostringstream::ate), space(true), context(){}
    std::ostringstream ss;
    bool space;
    LoggerType loggerType;
    LoggerContext context;
  };

public:
  LoggerStream();
  LoggerStream(std::string *s);
  ~LoggerStream();

  inline LoggerStream& operator<<(bool t) { stream->ss<<(t ? "true" : "false"); return maybeSpace(); }
  inline LoggerStream& operator<<(char t) { stream->ss<< t; return maybeSpace(); }
  inline LoggerStream& operator<<(unsigned char t) { stream->ss<< t; return maybeSpace(); }
  inline LoggerStream& operator<<(short t) { stream->ss << t; return maybeSpace(); }
  inline LoggerStream& operator<<(unsigned short t) { stream->ss << t; return maybeSpace(); }
  inline LoggerStream& operator<<(int t) { stream->ss<< t; return maybeSpace(); }
  inline LoggerStream& operator<<(unsigned int t) { stream->ss<< t; return maybeSpace(); }
  inline LoggerStream& operator<<(long t) { stream->ss<< t; return maybeSpace(); }
  inline LoggerStream& operator<<(long long t) { stream->ss<< t; return maybeSpace(); }
  inline LoggerStream& operator<<(float t) { stream->ss<< t; return maybeSpace(); }
  inline LoggerStream& operator<<(double t) { stream->ss<< t; return maybeSpace(); }
  inline LoggerStream& operator<<(std::string s) { stream->ss << s; return maybeSpace(); }
  inline LoggerStream& operator<<(const char* s) { stream->ss << s; return maybeSpace(); }
  inline LoggerStream& space() { stream->space = true; stream->ss << ' '; return *this; }
  inline LoggerStream& nospace() { stream->space = false; return *this; }
  inline LoggerStream& maybeSpace() { if (stream->space) stream->ss << ' '; return *this; }

  void toConsole(LoggerType type, const LoggerContext &context,
                 std::string logBuffer);

private:
  void mkTimeSpec(std::ostringstream& ss);

public:
  struct Stream *stream;
};

class Logger
{
public:
  Logger() : context(){}
  Logger(const char *fileName, const char *functionName, int lineNumber)
    : context(fileName, functionName, lineNumber) {}

  LoggerStream Debug() const;
  LoggerStream Info() const;
  LoggerStream Warning() const;
  LoggerStream Critical() const;
  LoggerStream Error() const;

protected:
  LoggerContext context;
};

#define LogD Logger(__FILE__, __FUNCTION__, __LINE__).Debug()
#define LogI Logger(__FILE__, __FUNCTION__, __LINE__).Info()
#define LogW Logger(__FILE__, __FUNCTION__, __LINE__).Warning()
#define LogC Logger(__FILE__, __FUNCTION__, __LINE__).Critical()
#define LogE Logger(__FILE__, __FUNCTION__, __LINE__).Error()
