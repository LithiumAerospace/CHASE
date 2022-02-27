#pragma once

#include <chrono>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

#define LOG_SILENT 0
#define LOG_ERR 1
#define LOG_ERROR 1
#define LOG_WARN 2
#define LOG_WARNING 2
#define LOG_INFO 3
#define LOG_DEBUG 4
#define LOG_DEFAULT 4

#define BSLOG_DEBUG "[ DEBUG   ]"
#define BSLOG_ERROR "\033[0;31m[ ERROR   ]\033[0;0m"
#define BSLOG_WARNING "\033[0;33m[ WARNING ]\033[0;0m"
#define BSLOG_INFO "\033[0;34m[ INFO    ]\033[0;0m"

class logger {
 public:
  inline logger(std::ostream&, std::string n);
  template <typename T>
  friend logger& operator<<(logger& l, const T& s);
  inline logger& operator()(unsigned ll);
  inline void flush() { _fac.flush(); }
  friend std::string prep_level(logger& l);
  friend std::string prep_time(logger& l);
  friend std::string prep_name(logger& l);
  static unsigned& _loglevel() {
    static unsigned _ll_internal = LOG_DEFAULT;
    return _ll_internal;
  };
  inline void set_log_level(unsigned ll) { _loglevel() = ll; }

 private:
  unsigned _message_level;
  std::ostream& _fac;
  std::string _name;
};

inline std::string prep_level(logger& l);
inline std::string prep_time(logger& l);
inline std::string prep_name(logger& l);

template <typename T>
logger& operator<<(logger& l, const T& s) {
  if (l._message_level <= l._loglevel()) {
    l._fac << s;
    return l;
  } else {
    return l;
  }
}

logger::logger(std::ostream& f, std::string n)
    : _message_level(LOG_SILENT), _fac(f), _name(n) {
}

logger& logger::operator()(unsigned ll) {
  _message_level = ll;
  if (_message_level <= _loglevel()) {
    std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();
    std::time_t t = std::chrono::system_clock::to_time_t(now);
    char ms[4];
    sprintf(ms, "%03li", std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count() % 1000);
    _fac << prep_level(*this) << std::put_time(std::localtime(&t), " [%F %T.") << ms << "] [" << _name << "]: ";
  }
  return *this;
}

std::string prep_level(logger& l) {
  switch (l._message_level) {
    case LOG_ERR:
      return BSLOG_ERROR;
      break;
    case LOG_WARN:
      return BSLOG_WARNING;
      break;
    case LOG_INFO:
      return BSLOG_INFO;
      break;
    case LOG_DEBUG:
      return BSLOG_DEBUG;
      break;
    default:
      return "";
  }
  return "";
}
