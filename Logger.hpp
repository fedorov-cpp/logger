#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <fstream>
#include <ctime>
#include <iomanip>

/*
 * HOW TO:
 * 1. create Logger instance using Logger::Type and Logger::Level
 * 2. call proper level function {trc, dbg, inf, ...}
 */

class Logger {
  public:
    enum class Type {
        file, console
    };

    enum class Level {
        CRIT, ERR, WARN, INFO, DEBUG, TRACE
    };

    /* @type defines where log messages should be printed */
    /* @name defines log filename */
    /* @level limits messages from appearing in log */
    Logger(Type, std::string name, Level);
    virtual ~Logger();

    virtual std::ostream &trc();
    virtual std::ostream &dbg();
    virtual std::ostream &inf();
    virtual std::ostream &wrn();
    virtual std::ostream &err();
    virtual std::ostream &crt();

  protected:
    static std::string levelToStr(Level);
    virtual std::ostream &getStream(Level);
    virtual bool isValidLevel(Level);
    virtual void insertLineHeader(Level);

  private:
    std::string name_;
    Level level_;

    std::ostream *stream_;
    std::filebuf filebuf_;
    std::ostream *null_;
};

#endif //LOGGER_H
