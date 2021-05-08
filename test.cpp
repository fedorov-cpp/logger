#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <Logger.hpp>

#include <filesystem>

namespace fs = std::filesystem;

TEST_CASE("Different logging message levels", "[Logger]") {
  const std::string filename = "TestLogger";

  const auto check_logging_level = [&](const std::string &level) {
    const fs::path filepath = filename + ".log";
    std::ifstream ifs(filepath);
    std::string line;
    std::getline(ifs, line);
    fs::remove(filepath);
    const size_t max_start_pos = 10UL;
    return line.rfind(level, max_start_pos);
  };

  SECTION("Trace") {
    Logger logger(Logger::Type::file, filename, Logger::Level::TRACE);
    logger.trc() << "trace logging message" << std::endl;
    REQUIRE(check_logging_level("TRC") != std::string::npos);
  }

  SECTION("Debug") {
    Logger logger(Logger::Type::file, filename, Logger::Level::TRACE);
    logger.dbg() << "debug logging message" << std::endl;
    REQUIRE(check_logging_level("DBG") != std::string::npos);
  }

  SECTION("Info") {
    Logger logger(Logger::Type::file, filename, Logger::Level::TRACE);
    logger.inf() << "info logging message" << std::endl;
    REQUIRE(check_logging_level("INF") != std::string::npos);
  }

  SECTION("Warning") {
    Logger logger(Logger::Type::file, filename, Logger::Level::TRACE);
    logger.wrn() << "warning logging message" << std::endl;
    REQUIRE(check_logging_level("WRN") != std::string::npos);
  }

  SECTION("Error") {
    Logger logger(Logger::Type::file, filename, Logger::Level::TRACE);
    logger.err() << "error logging message" << std::endl;
    REQUIRE(check_logging_level("ERR") != std::string::npos);
  }

  SECTION("Critical") {
    Logger logger(Logger::Type::file, filename, Logger::Level::TRACE);
    logger.crt() << "critical logging message" << std::endl;
    REQUIRE(check_logging_level("CRT") != std::string::npos);
  }
}

TEST_CASE("Different Logger levels", "[Logger]") {
  const std::string filename = "TestLogger";

  const auto check_logging_level = [&](const std::vector<std::string> &levels) {
    const fs::path filepath = filename + ".log";
    std::ifstream ifs(filepath);
    std::string line;
    std::vector<std::string::size_type> result;
    for (const auto &level: levels) {
      std::getline(ifs, line);
      fs::remove(filepath);
      const size_t max_start_pos = 10UL;
      result.emplace_back(line.rfind(level, max_start_pos));
    }
    return result;
  };

  const auto do_log = [](Logger &logger) {
    logger.trc() << "trace logging message" << std::endl;
    logger.dbg() << "debug logging message" << std::endl;
    logger.inf() << "info logging message" << std::endl;
    logger.wrn() << "warning logging message" << std::endl;
    logger.err() << "error logging message" << std::endl;
    logger.crt() << "critical logging message" << std::endl;
  };

  SECTION("Trace") {
    Logger logger(Logger::Type::file, filename, Logger::Level::TRACE);
    do_log(logger);
    const auto result = check_logging_level({"TRC", "DBG", "INF", "WRN", "ERR", "CRT"});
    REQUIRE(std::all_of(result.begin(), result.end(), [](const size_t pos) { return pos != std::string::npos; }));
  }

  SECTION("Debug") {
    Logger logger(Logger::Type::file, filename, Logger::Level::DEBUG);
    do_log(logger);
    const auto result = check_logging_level({"DBG", "INF", "WRN", "ERR", "CRT"});
    REQUIRE(std::all_of(result.begin(), result.end(), [](const size_t pos) { return pos != std::string::npos; }));
  }

  SECTION("Info") {
    Logger logger(Logger::Type::file, filename, Logger::Level::INFO);
    do_log(logger);
    const auto result = check_logging_level({"INF", "WRN", "ERR", "CRT"});
    REQUIRE(std::all_of(result.begin(), result.end(), [](const size_t pos) { return pos != std::string::npos; }));
  }

  SECTION("Warning") {
    Logger logger(Logger::Type::file, filename, Logger::Level::WARN);
    do_log(logger);
    const auto result = check_logging_level({"WRN", "ERR", "CRT"});
    REQUIRE(std::all_of(result.begin(), result.end(), [](const size_t pos) { return pos != std::string::npos; }));
  }

  SECTION("Error") {
    Logger logger(Logger::Type::file, filename, Logger::Level::ERR);
    do_log(logger);
    const auto result = check_logging_level({"ERR", "CRT"});
    REQUIRE(std::all_of(result.begin(), result.end(), [](const size_t pos) { return pos != std::string::npos; }));
  }

  SECTION("Critical") {
    Logger logger(Logger::Type::file, filename, Logger::Level::CRIT);
    do_log(logger);
    const auto result = check_logging_level({"CRT"});
    REQUIRE(std::all_of(result.begin(), result.end(), [](const size_t pos) { return pos != std::string::npos; }));
  }
}

TEST_CASE("Log file has expected extension", "[Logger]") {
  const std::string name = "TestLogger";
  Logger logger(Logger::Type::file, name, Logger::Level::TRACE);
  REQUIRE(fs::exists(name + ".log"));
}
