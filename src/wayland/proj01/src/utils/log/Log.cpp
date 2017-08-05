#include <string.h>
#include <ctime>
#include <stdlib.h>
#include <unistd.h>
#include <linux/unistd.h>
#include <sys/syscall.h>   /* For SYS_xxx definitions */
#include <sys/time.h>
#include <sys/types.h>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <map>
#include <iomanip>
#include "Log.hpp"

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#ifndef gettid
#define gettid() syscall(__NR_gettid)
#endif

// "\x1b[0m" or "\e[0m"
#define NONE                 "\e[0m"
#define BLACK                "\e[0;30m"
#define L_BLACK              "\e[1;30m"
#define RED                  "\e[0;31m"
#define L_RED                "\e[1;31m"
#define GREEN                "\e[0;32m"
#define L_GREEN              "\e[1;32m"
#define BROWN                "\e[0;33m"
#define YELLOW               "\e[1;33m"
#define BLUE                 "\e[0;34m"
#define L_BLUE               "\e[1;34m"
#define PURPLE               "\e[0;35m"
#define L_PURPLE             "\e[1;35m"
#define CYAN                 "\e[0;36m"
#define L_CYAN               "\e[1;36m"
#define GRAY                 "\e[0;37m"
#define WHITE                "\e[1;37m"

#define BOLD                 "\e[1m"
#define UNDERLINE            "\e[4m"
#define BLINK                "\e[5m"
#define REVERSE              "\e[7m"
#define HIDE                 "\e[8m"
#define CLEAR                "\e[2J"
#define CLRLINE              "\r\e[K" //or "\e[1K\r"

#define ANSI_NONE NONE

#define ANSI_RED(fmt) (RED##fmt##NONE)
#define ANSI_GREEN(fmt) (GREEN##fmtNONE)
#define ANSI_BROWN(fmt) (BROWN##fmtNONE)
#define ANSI_BLUE(fmt) (BLUE##fmt##NONE)
#define ANSI_YELLOW(fmt) (YELLOW##fmt##NONE)

#define _ANSI_RED RED
#define _ANSI_GREEN GREEN
#define _ANSI_BROWN BROWN
#define _ANSI_BLUE BLUE
#define _ANSI_GRAY GRAY
#define _ANSI_L_RED L_RED
#define _ANSI_YELLOW YELLOW

#ifdef USE_LOG_CAT
#include <base/log/Log.h>
#endif

#ifdef USE_LOG_CAT
bool LoggerStream::useLogCat = true;
#endif
std::string LoggerStream::TAG = "";
bool LoggerStream::useFileBackEnd = false;
std::ofstream LoggerStream::logOFStream;
int LoggerStream::fileMaxSize = 40 * 1024 *1024; // default: 40M
const char* LoggerStream::logPath = "/data/srv.log";

class LogLevel {
public:
    LogLevel() {
        char* str = getenv("LOG_LEVEL");
        if (str != NULL) {
            static struct {
                LoggerType type;
                const std::string str;
            } arr[] = {
                {E_Debug, "D"},
                {E_Info, "I"},
                {E_Warning, "W"},
                {E_Critical, "C"},
                {E_Error, "E"},
                {E_FastBoot, "F"},
            };

            for (auto &item : arr) {
                if (item.str == str) {
                    limit = item.type;
                    break;
                }
            }
        }
    }

    enum LoggerType getLimit() {
        return limit;
    }

    LoggerType limit = E_Debug;
};

class LogFileFeature {
public:
    LogFileFeature() {
        char* str = getenv("LOG_TOFILE");
        if (str != NULL) {
            if (std::string("1") == str) {
                LoggerStream::useFileBackEnd = true;
            }
        }
        str = getenv("LOG_FILE_PATH");
        if (str != NULL) {
            LoggerStream::logPath = strdup(str);
        }
    }
};

class LogFileMaxSize {
public:
    LogFileMaxSize() {
        char* str = getenv("LOG_FILE_MAXSIZE");
        if (str != NULL) {
            int size = atoi(str);
            if (size != 0) {
                LoggerStream::fileMaxSize = size;
            }
        }
    }
};

static LogLevel logLevel;
static LogFileFeature logFileFeature;
static LogFileMaxSize logFileMaxSize;

// class LoggerStream
LoggerStream::LoggerStream()
    : stream(new Stream()) {}

LoggerStream::LoggerStream(std::string *s)
    : stream(new Stream(s)) {}

LoggerStream::~LoggerStream()
{
    // depend on env["LOG_LEVEL"]
    if (logLevel.getLimit() <= stream->loggerType) {
        std::ostringstream sstimestamp;
        mkTimeSpec0(sstimestamp);

        toConsole(stream->loggerType, stream->context,
                  stream->ss.str(), sstimestamp);
        if (useFileBackEnd) {
            toFile(stream->loggerType, stream->context,
                   stream->ss.str(), sstimestamp);
        }
#ifdef USE_LOG_CAT
        if (useLogCat) {
            toLogCat(stream->loggerType, stream->context,
                     stream->ss.str(), sstimestamp);
        }
#endif
    }

    delete stream;
}

void
LoggerStream::SetTag(std::string tag)
{
    TAG = tag;
}

void
LoggerStream::mkTag(std::ostringstream& ss)
{
    ss << TAG.c_str();
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
    case E_Debug: ss << "D"; ret = _ANSI_GRAY; break;
    case E_Info: ss << "I"; ret = _ANSI_BLUE; break;
    case E_Warning: ss << "W"; ret = _ANSI_BROWN; break;
    case E_Critical:ss << "C"; ret = _ANSI_L_RED; break;
    case E_Error: ss << "E"; ret = _ANSI_RED; break;
    case E_FastBoot: ss << "F"; ret = _ANSI_YELLOW; break;
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
       << ",L" << context.line << ": ";
}

void
LoggerStream::mkOuput(LoggerType type, const LoggerContext &context,
                      const std::string &logBuffer,
                      const std::ostringstream &sstimestamp,
                      std::ostringstream& ss)
{
    ss << _ANSI_GREEN << sstimestamp.str() << ANSI_NONE;
    ss << _ANSI_BROWN << ' ';
    mkTag(ss);
    ss << ANSI_NONE;
    const char* color = mkType(type, context, ss);
    mkBannaer(type, context, ss);

    ss << color << logBuffer << ANSI_NONE;
}

void
LoggerStream::toConsole(LoggerType type,
                        const LoggerContext &context,
                        const std::string &logBuffer,
                        const std::ostringstream &sstimestamp)
{
    std::ostringstream ss;
    mkOuput(type, context, logBuffer, sstimestamp, ss);

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

void
LoggerStream::toFile(LoggerType type, const LoggerContext &context,
                     const std::string &logBuffer,
                     const std::ostringstream &sstimestamp)
{
    if (!logOFStream.is_open()) {
        logOFStream.open(logPath);
    }

    // relocation
    if (LoggerStream::logOFStream.tellp() > fileMaxSize) {
        LoggerStream::logOFStream.seekp(0);
    }

    std::ostringstream ss;
    mkOuput(type, context, logBuffer, sstimestamp, ss);

    logOFStream << ss.str() << std::endl;
}

#ifdef USE_LOG_CAT
void
LoggerStream::toLogCat(LoggerType type,
                       const LoggerContext &context,
                       const std::string &logBuffer,
                       const std::ostringstream &sstimestamp)
{

#ifndef LOG_TAG
#define LOG_TAG (TAG.c_str())
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
    case E_FastBoot: break;
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

LoggerStream Logger::__xxFastBoot() const
{
    return genLoggerStream(E_FastBoot);
}

LoggerStream Logger::genLoggerStream(enum LoggerType type) const
{
    LoggerStream ls;
    LoggerContext &ctxt = ls.stream->context;
    ctxt.copy(context);
    ls.stream->loggerType = type;
    return ls;
}

__xxScopeLogger::__xxScopeLogger(std::string tag,
                                 const char* file,
                                 const char* func,
                                 int line)
    : tag(tag)
    , file(file)
    , func(func)
    , line(line) {
    Logger(file, func, line).__xxDebug() << tag << "start";
}

__xxScopeLogger::~__xxScopeLogger() {
    Logger(file, func, line).__xxDebug() << tag << "done";
}
