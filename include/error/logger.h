//
// Created by przemek on 28.05.2020.
//

#ifndef VECC_LOGGER_H
#define VECC_LOGGER_H

#include "boost/iostreams/device/null.hpp"
#include "boost/iostreams/stream.hpp"
#include <iostream>
#include <vecc_include.h>

namespace vecc {
  namespace error {
    class Logger {
    public:
      explicit Logger(LogLevel logLevel, std::ostream &out = noOut);
      void putLog(LogLevel logLevel, const std::string &message);

      static Logger noLogger;

    private:
      std::ostream &out_;
      LogLevel logLevel_;

      // to allow non buffered no-output ostream
      class NullBuffer : public std::streambuf {
      public:
        int overflow(int c) override { return c; }
      };
      static NullBuffer noBuf;
      static std::ostream noOut;
    };
  } // namespace error

} // namespace vecc

#endif // VECC_LOGGER_H
