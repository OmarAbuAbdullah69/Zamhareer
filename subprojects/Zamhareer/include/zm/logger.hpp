#pragma once

#ifdef DEB_BUILD
#define LOG(...) logger::inst().log(__VA_ARGS__)
#define LOGINFO(...) logger::inst().logInfo(__VA_ARGS__)
#define LOGWARN(...) logger::inst().logWarn(__VA_ARGS__)
#define LOGERROR(...) logger::inst().logError(__VA_ARGS__)
#else
#define LOG(...)
#define LOGINFO(...)
#define LOGWARN(...)
#define LOGERROR(...)
#endif
#include "zm/external/zmprinter.hpp"
namespace zm {
class logger {
public:
  static logger &inst() {
    static logger l;
    return l;
  }
  template <typename... Args>
  void log(const char *message, const Args &...args) {
    mPrinter.print(message, args...);
  }
  template <typename... Args>
  void logInfo(const char *message, const Args &...args) {
    std::string m = "INFO:\n\t";
    m += message;
    m += '\n';
    mPrinter.print(m.c_str(), args...);
  }
  template <typename... Args>
  void logWarn(const char *message, const Args &...args) {
    std::string m = "WARN:\n\t";
    m += message;
    m += '\n';
    mPrinter.print(m.c_str(), args...);
  }
  template <typename... Args>
  void logError(const char *message, const Args &...args) {
    std::string m = "ERROR:\n\t";
    m += message;
    m += '\n';
    mPrinter.print(m.c_str(), args...);
  }

private:
  logger();
  printer mPrinter;
};
} // namespace zm
