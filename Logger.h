#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <fstream>
#include <ctime>
#include <iomanip>

/*
 * HOW TO:
 * 1. create Logger instance
 * 2. call proper level function {trc, dbg, inf, ...}
 */

class Logger {
  public:
    enum class Type {
        file, console
    };

    enum class Level {
        TRACE, DEBUG, INFO, WARN, ERR, CRIT
    };

    /* @type defines where log messages should be printed */
    /* @name defines log filename */
    /* @level limits messages from appearing in log */
    Logger(Type, std::string name, Level);
    ~Logger();

    inline std::ostream &trc() { return getStream(Level::TRACE); }
    inline std::ostream &dbg() { return getStream(Level::DEBUG); }
    inline std::ostream &inf() { return getStream(Level::INFO); }
    inline std::ostream &wrn() { return getStream(Level::WARN); }
    inline std::ostream &err() { return getStream(Level::ERR); }
    inline std::ostream &crt() { return getStream(Level::CRIT); }
    inline std::string getName() { return name_; }

  private:
    std::ostream &getStream(Level);
    bool isValidLevel(Level);
    static std::string levelToStr(Level);
    void insertLineHeader(Level);

    std::string name_;
    Level level_;

    std::ostream *stream_;
    std::filebuf filebuf_;
    std::ostream *null_;
};

#endif //LOGGER_H
