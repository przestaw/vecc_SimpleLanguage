//
// Created by przemek on 15.03.2020.
//

#ifndef VECC_LANG_OUTPUT_H
#define VECC_LANG_OUTPUT_H

#include <iostream>
#include <sstream>
#include <queue>
#include <mutex>
#include <condition_variable>

namespace vecc {

    // NOTE: FIXME : Is this class needed at all
    class Output{
    public:
        Output &getInstance();

        void setLogLevel(unsigned char logLevel);

        void putOutLine(const std::string &line);
        void putLogLine(const std::string &line, unsigned char logLevel);
        // TODO : void putLog(const LogStruct &log);
        // TODO : LogStruct -> level as enum, toString() etc

        void enableOutput();
        void clearBuffer();
        void disableOutput();

        std::string getOutput();
        std::string getLogging();
    protected:
        Output(std::ostream &out = std::cout, std::ostream &log = std::cerr) : out_(out), log_(log) {}
        virtual ~Output() {}
    private:
        // NOTE : exclusive access protection : mutex or atomic?
        bool outputing = true;
        unsigned char logLevel = 0;
        //streams
        std::ostream &out_;
        std::ostream &log_;
        //buffers, could be string or stringstream
        std::string outStr;
        std::string logStr; // NOTE : may be unnescesary -> used to pass information to User
    };

}

#endif //VECC_LANG_OUTPUT_H
