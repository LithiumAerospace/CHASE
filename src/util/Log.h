#pragma once

#include <algorithm>
#include <chrono>
#include <cmath>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

#define LOG_SILENT 0
#define LOG_ERR 1
#define LOG_ERROR 1
#define LOG_WARN 2
#define LOG_WARNING 2
#define LOG_INFO 3
#define LOG_DEBUG 4
#define LOG_DEFAULT 4

#define LOG_INIT_COUT(n) logger log(std::cout, n)

#define BSLOG_DEBUG "[ DEBUG   ]"
#define BSLOG_ERROR "\033[0;31m[ ERROR   ]\033[0;0m"
#define BSLOG_WARNING "\033[0;33m[ WARNING ]\033[0;0m"
#define BSLOG_INFO "\033[0;34m[ INFO    ]\033[0;0m"

class logger {
 public:
  inline logger(std::ostream&, unsigned, std::string);
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

logger::logger(std::ostream& f, unsigned ll, std::string n)
    : _message_level(LOG_SILENT), _fac(f), _name(n) {
  _loglevel() = ll;
}

logger& logger::operator()(unsigned ll) {
  _message_level = ll;
  if (_message_level <= _loglevel()) {
    _fac << prep_level(*this) << prep_time(*this) << prep_name(*this) << ": ";
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

std::string prep_time(logger& l) {
  time_t _now;
  time(&_now);
  struct tm* t;
  t = localtime(&_now);
  std::string s, m, h, D, M, Y;
  s = std::to_string(t->tm_sec);
  m = std::to_string(t->tm_min);
  h = std::to_string(t->tm_hour);
  D = std::to_string(t->tm_mday);
  M = std::to_string(t->tm_mon + 1);
  Y = std::to_string(t->tm_year + 1900);

  if (t->tm_sec < 10) s = "0" + s;
  if (t->tm_min < 10) m = "0" + m;
  if (t->tm_hour < 10) h = "0" + h;
  if (t->tm_mday < 10) D = "0" + D;
  if (t->tm_mon + 1 < 10) M = "0" + M;

  std::string ret =
      " [" + Y + "-" + M + "-" + D + " " + h + ":" + m + ":" + s + "]";

  return ret;
}

std::string prep_name(logger& l) { return " [" + l._name + "]"; }
