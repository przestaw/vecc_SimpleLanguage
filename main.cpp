#include "general_defines.h"
#include <vecc_include.h>
#include <iostream>
#include <boost/program_options.hpp>
#include <scanner/scanner.h>
#include <fstream>
#include <error/exeception.h>
#include <parser/parser.h>
#include "scanner/reader.h"

using namespace boost::program_options;

struct Params {
    bool run = false;
    std::vector<std::string> files;
    vecc::LogLevel verbosity = vecc::LogLevel::FullLog;
} params;

inline void parseParams(int argc, char *argv[]) {
    try {
        options_description desc{"Options"};
        desc.add_options()
                ("help,h", "Help screen")
                ("input,i", value<std::vector<std::string>>()->multitoken(), "Input file")
                ("verbosity,v", value<uint8_t>()->default_value(static_cast<uint8_t>(vecc::LogLevel::FullLog)),
                 "verbosity level : \n"
                 "\t 0 - no information\n"
                 "\t 1 - errors\n");//TODO

        variables_map vm;
        store(parse_command_line(argc, argv, desc), vm);
        notify(vm);

        /* Parse options */
        if (vm.count("help")) {
            std::cout << desc << '\n';
        } else {
            if (vm.count("input") > 0) {
                params.run = true;
                params.files = vm["input"].as<std::vector<std::string>>();
                uint8_t verbosity = vm["verbosity"].as<uint8_t>();
                if (verbosity >= static_cast<uint8_t>(vecc::LogLevel::FullLog)) {
                    params.verbosity = vecc::LogLevel::FullLog;
                } else {
                    params.verbosity = vecc::LogLevel{verbosity};
                }
            }
        }
    } catch (const error &ex) {
        std::cerr << ex.what() << " !\n";
    }
}

void parseFile(vecc::Parser &parser,const std::string &filename) {
    std::ifstream file;
    file.open(filename);

    if (!file.fail()) {
        try {
            parser.setSource(std::make_unique<vecc::Reader>(file, filename));
            parser.parse();
        } catch (vecc::Exception &error) {
            if(params.verbosity >= vecc::LogLevel::Errors){
                std::cerr << error.what() << std::endl;
            } else {
                (void)error;
            }
        }
    } else {
        if(params.verbosity >= vecc::LogLevel::Errors){
            std::cerr << (FRED(BOLD("ARG ERROR"))" Invalid file : " + filename);
        }
    }

    file.close();
}

int main(int argc, char *argv[]) {
    std::cout << "Hello, World!\n"
              << "from vecc lang project\n"
              << "for " BOLD("TKOM ") DIM("[Compilation Techniques]") " classes\n"
              << FBLU(INV("by Stawczyk Przemyslaw"))
              << std::endl; //flush stream

    parseParams(argc, argv);
    if (params.run) {
        std::cout << FGRN(BOLD("START\n"));

        vecc::Parser parser(std::cout);

        for(auto  &it : params.files){
            parseFile(parser, it);
        }

        auto prog = parser.getProgram();

        try {
            prog->run();
        } catch (vecc::Exception &error) {
            if(params.verbosity >= vecc::LogLevel::Errors){
                std::cerr << error.what() << std::endl;
            } else {
                (void)error;
            }
        }

        std::cout << FRED(BOLD("END\n"));
    }
    return 0;
}
