#include "general_defines.h"
#include <iostream>
#include <boost/program_options.hpp>
#include "scanner/reader.h"

using namespace boost::program_options;

struct Params {
    bool run = false;
    std::string file;
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
            //TODO : parse option

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
              << FBLU(INV("by Stawczyk Przemyslaw") "\n");

    Params params = parseParams(argc, argv);
    params.run = true;
    if(params.run){
        //TODO
        std::cout << FGRN(BOLD("RUN\n"));

        std::cout << FRED(BOLD("END\n"));
    }
    return 0;
}
