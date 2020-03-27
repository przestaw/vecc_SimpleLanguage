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
    std::string file = "";
    vecc::LogLevel verbosity = vecc::LogLevel::FullLog;
} params;

inline Params parseParams(int argc, char *argv[]) {
    try {
        options_description desc{"Options"};
        desc.add_options()
                ("help,h", "Help screen")
                ("input,i", value<std::string>(), "Input file")
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
                params.file = vm["input"].as<std::string>();
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

void parseFile(vecc::Parser &parser){
    std::ifstream file;
    file.open(params.file);

    try {
        if (file.fail()) { throw vecc::Exception(FRED(BOLD("ARG ERROR"))" Invalid file"); }
        parser.setSource(std::make_unique<vecc::Reader>(file));
        parser.parse();
    } catch (vecc::Exception &error) {
        if(params.verbosity >= vecc::LogLevel::Errors){
            std::cerr << error.what() << std::endl;
        } else {
            (void)error;
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
        vecc::Parser parser;

        //NOTE : WIP
        //TODO : REWORK
        parseFile(parser);

        auto prog = parser.getProgram();

        prog->run();


        std::cout << FRED(BOLD("END\n"));
    }
    return 0;
}
