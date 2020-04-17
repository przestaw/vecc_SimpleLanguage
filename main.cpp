#include "general_defines.h"
#include <iostream>
#include <boost/program_options.hpp>
#include <scanner/scanner.h>
#include <fstream>
#include <vecc_exeception.h>
#include "scanner/reader.h"

using namespace boost::program_options;

struct Params {
    bool run = false;
    std::string file = "";
    uint8_t verbosity = 0;
};

// NOTE : consider ref to params instead of return ??
inline Params parseParams(int argc, char *argv[]){
    Params params = Params();
    try {
        options_description desc{"Options"};
        desc.add_options()
                ("help,h", "Help screen")
                ("input,i", value<std::string>(), "Input file")
                ("verbosity,v", value<uint8_t>()->default_value(0), "verbosity level");

        variables_map vm;
        store(parse_command_line(argc, argv, desc), vm);
        notify(vm);

        /* Parse options */
        if (vm.count("help")) {
            std::cout << desc << '\n';
        } else {
            if(vm.count("input") > 0){
                params.run = true;
                params.file = vm["input"].as<std::string>();
                params.verbosity = vm["verbosity"].as<uint8_t>();
            }
        }
    } catch (const error &ex) {
        std::cerr << ex.what() << " !\n";
    }
    return params;
}

int main(int argc, char *argv[]) {
    std::cout << "Hello, World!\n"
              << "from vecc lang project\n"
              << "for " BOLD("TKOM ") DIM("[Compilation Techniques]") " classes\n"
              << FBLU(INV("by Stawczyk Przemyslaw"))
              << std::endl; //flush stream

    Params params = parseParams(argc, argv);
    if(params.run){
        std::cout << FGRN(BOLD("START\n"));
        std::ifstream file;
        file.open(params.file);
        vecc::Scanner scanner(std::make_unique<vecc::Reader>(file, params.file));
        vecc::Token token;

        try{
            if(file.fail()){throw vecc::Exception(FRED(BOLD("ARG ERROR"))" Invalid file");}
            // NOTE: Exception to be used/included in bigger/final function
            do{
                token = scanner.parseToken();
                std::cout << INV("Token read") " : " <<  token.toString() << '\n';
            }while(token.getType() != vecc::Token::Type::NaT && token.getType() != vecc::Token::Type::EoF);
        } catch (vecc::Exception &error){
            std::cerr << error.what() << std::endl;
        }

        file.close();

        std::cout << FRED(BOLD("END\n"));
    }
    return 0;
}
