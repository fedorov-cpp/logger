#include <unordered_map>

#include "Logger.h"

namespace {
  struct FS_EnumClassHash {
    template<typename T>
    std::size_t operator()(T t) const {
      return static_cast<std::size_t>(t);
    }
  };
}

Logger::Logger(Type type, std::string name, Level level)
    : name_(std::move(name)), level_(level) {
  if (type == Type::file) {
    filebuf_.open(name_ + ".log", std::ios_base::app);
    stream_ = new std::ostream(&filebuf_);
  } else if (type == Type::console) {
    stream_ = new std::ostream(std::cout.rdbuf());
  }
  null_ = new std::ostream(nullptr);
}

Logger::~Logger() {
  if (filebuf_.is_open()) {
    filebuf_.close();
  }
  delete stream_;
  delete null_;
}

std::ostream &Logger::getStream(Level level) {
  if (isValidLevel(level)) {
    insertLineHeader(level);
    return *stream_;
  } else {
    return *null_;
  }
}

bool Logger::isValidLevel(Level level) {
  return level_ >= level;
}

std::string Logger::levelToStr(Level level) {
  static const std::unordered_map<Level, std::string, FS_EnumClassHash> MAP = {
      {Level::TRACE, "      TRC"},
      {Level::DEBUG, "      DBG"},
      {Level::INFO,  "   INF   "},
      {Level::WARN,  "   WRN   "},
      {Level::ERR,   "ERR      "},
      {Level::CRIT,  "CRT      "},
  };

  const auto it = MAP.find(level);
  if (it != MAP.end()) {
    return it->second;
  }

  throw std::runtime_error{"Got unknown level."};
}

void Logger::insertLineHeader(Level level) {
  const std::string sLevel = levelToStr(level);

  // get current time
  const auto t = time(nullptr);
  const auto tm = *localtime(&t);

  *stream_ << sLevel << " | "
           << std::put_time(&tm, "%d.%m.%Y %H:%M:%S") << " | ";
}
