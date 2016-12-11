#pragma once

#include <string>
#include <sstream>

//#define NOTUSED() __attribute__((unused))
#define NOTUSED(v) for (;;) { (void)(1 ? (void)0 : ( (void)(v) ) ); break; }

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
                 const std::string &logBuffer,
                 const std::ostringstream &sstimestamp);
#ifdef USE_LOG_CAT
  void toLogCat(LoggerType type, const LoggerContext &context,
                const std::string &logBuffer,
                const std::ostringstream &sstimestamp);
#endif

private:
  void mkTag(std::ostringstream& ss);
  void mkTimeSpec0(std::ostringstream& ss);
  void mkTimeSpec1(std::ostringstream& ss);
  void mkBannaer(LoggerType, const LoggerContext &, std::ostringstream& ss);
  const char* mkType(LoggerType, const LoggerContext &, std::ostringstream& ss);

public:
  struct Stream *stream;
#ifdef USE_LOG_CAT
  static bool useLogCat;
#endif
  static std::string TAG;
};

class Logger
{
public:
  Logger() : context(){}
  Logger(const char *fileName, const char *functionName, int lineNumber)
    : context(fileName, functionName, lineNumber) {}
  Logger(const char *functionName, int lineNumber)
    : context("", functionName, lineNumber) {}

  LoggerStream __xxDebug() const;
  LoggerStream __xxInfo() const;
  LoggerStream __xxWarning() const;
  LoggerStream __xxCritical() const;
  LoggerStream __xxError() const;

private:
  LoggerStream genLoggerStream(enum LoggerType type) const;

protected:
  LoggerContext context;
};

#define LogD Logger(__FILE__, __FUNCTION__, __LINE__).__xxDebug()
#define LogI Logger(__FILE__, __FUNCTION__, __LINE__).__xxInfo()
#define LogW Logger(__FILE__, __FUNCTION__, __LINE__).__xxWarning()
#define LogC Logger(__FILE__, __FUNCTION__, __LINE__).__xxCritical()
#define LogE Logger(__FILE__, __FUNCTION__, __LINE__).__xxError()

#define __LogFormat(...)                              \
  char __xxs[100];snprintf(__xxs,100,__VA_ARGS__);
#ifdef Err
#undef Err
#endif
#define Err(...) {__LogFormat(__VA_ARGS__); LogE<<__xxs;}
#ifdef Info
#undef Info
#endif
#define Info(...) {__LogFormat(__VA_ARGS__); LogI<<__xxs;}
#ifdef Warn
#undef Warn
#endif
#define Warn(...) {__LogFormat(__VA_ARGS__); LogW<<__xxs;}
#ifdef Debug
#undef Debug
#endif
#define Debug(...) {__LogFormat(__VA_ARGS__); LogD<<__xxs;}

#ifdef loge
#undef loge
#endif
#define loge Err
#ifdef logi
#undef logi
#endif
#define logi Info
#ifdef logw
#undef logw
#endif
#define logw Warn
#ifdef logd
#undef logd
#endif
#define logd Debug
