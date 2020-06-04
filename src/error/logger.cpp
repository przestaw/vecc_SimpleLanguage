//
// Created by przemek on 28.05.2020.
//
#include <error/logger.h>

using namespace vecc::error;

Logger::NullBuffer Logger::noBuf;
std::ostream Logger::noOut(&noBuf);
Logger Logger::noLogger = Logger(vecc::LogLevel::NoLog);

Logger::Logger(vecc::LogLevel logLevel, std::ostream& out)
    : out_(out), logLevel_(logLevel) {
}

void Logger::putLog(vecc::LogLevel logLevel, const std::string& message) {
  if (logLevel <= logLevel_) {
    out_ << message;
  }
}
