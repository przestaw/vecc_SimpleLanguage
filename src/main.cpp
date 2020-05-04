#include "general_defines.h"
#include "scanner/reader.h"
#include <boost/program_options.hpp>
#include <error/exeception.h>
#include <fstream>
#include <iostream>
#include <parser/parser.h>
#include <scanner/scanner.h>
#include <vecc_include.h>

using namespace boost::program_options;
using namespace vecc;
using namespace vecc::error;
using namespace vecc::ast;

/**
 * Params struct for storing runtime params
 */
struct Params {
  bool run = false; //!< determines if there are files to parse&run
  std::vector<std::string> files = {};              //!< files to be parsed
  LogLevel verbosity             = LogLevel::NoLog; //!< log level
  bool fibLib                    = false;           //!< Fibonacci library
  bool veccLib                   = false;           //!< vecc library
} params;                                           //!< global Params object

/**
 * Function for arguments parsing
 * @param argc arguments count from stdin
 * @param argv arguments array
 */
inline void parseParams(int argc, char *argv[]) {
  try {
    options_description desc{"Options"};
    desc.add_options()("help,h", "Help screen")(
        "input,i", value<std::vector<std::string>>()->multitoken(),
        "Input file")("vec", bool_switch(&params.veccLib)->default_value(false),
                      "Incude standard vec library")(
        "fib", bool_switch(&params.fibLib)->default_value(false),
        "Incude Fibonacci library")(
        "verbosity,v",
        value<uint8_t>()->default_value(static_cast<uint8_t>(LogLevel::NoLog)),
        "verbosity level : \n"
        "\t 0  -  no information\n"
        "\t 1  -  errors\n"
        "\t 2  -  errors & information about parsed files\n"
        "\t 3  -  errors & files & any created function\n"
        "\t 4  -  errors & files & functions & any parsed token\n"
        "\t 5+ -  full available log\n");

    variables_map vm;
    store(parse_command_line(argc, argv, desc), vm);
    notify(vm);

    /* Parse options */
    if (vm.count("help")) {
      std::cout << desc << '\n';
    } else {
      if (vm.count("input") > 0) {
        params.run = true;

        params.files      = vm["input"].as<std::vector<std::string>>();
        uint8_t verbosity = vm["verbosity"].as<uint8_t>() - '0';
        if (verbosity >= static_cast<uint8_t>(LogLevel::FullLog)) {
          params.verbosity = LogLevel::FullLog;
        } else {
          params.verbosity = static_cast<LogLevel>(verbosity);
        }
      }
    }
  } catch (const boost::program_options::error &ex) {
    std::cerr << ex.what() << " !\n";
  }
}

/**
 * Helper function for stream parsing
 * @param parser Parser used in the process
 * @param name of the stream to be parsed
 * @param stream stream to be parsed
 */
inline void parseStream(Parser &parser, const std::string &name,
                        std::istream &stream) {
  try {
    parser.setSource(std::make_unique<Reader>(stream, name));
    parser.parse();
  } catch (Exception &error) {
    if (params.verbosity >= LogLevel::Errors) {
      std::cerr << error.what() << std::endl;
    } else {
      (void)error;
    }
  }
}

/**
 * Helper function for single file parsing
 * @param parser Parser used in the process
 * @param filename name of the file to be parsed
 */
void parseFile(Parser &parser, const std::string &filename) {
  std::ifstream file;
  file.open(filename);

  if (!file.fail()) {
    parseStream(parser, filename, file);
  } else {
    if (params.verbosity >= LogLevel::Errors) {
      std::cerr << (FRED(BOLD("ARG ERROR")) " Invalid file : " + filename);
    }
  }

  file.close();
}

/**
 * Main function
 * @return 0 on success
 */
int main(int argc, char *argv[]) {
  std::cout << "Hello, World!\n"
            << "from vecc lang project\n"
            << "for " BOLD("TKOM ") DIM("[Compilation Techniques]") " classes\n"
            << FBLU(INV("by Stawczyk Przemyslaw")) << std::endl; // flush stream

  parseParams(argc, argv);
  if (params.run) {
    if (params.verbosity > LogLevel::NoLog) {
      std::cout << FGRN(BOLD("START\n"));
    }

    Parser parser(params.verbosity, std::cout);

    // include vecc library
    if (params.veccLib) {
      if (params.verbosity >= LogLevel::ParsedFiles) {
        std::cout << FBLU(BOLD("File Log : \n")) "Parse internal lib : " FBLU(
            "vec lib") "\n";
      }
      std::stringstream str(libraries::veccLibrary);
      parseStream(parser, "vecc library", str);
    }

    // include fib library
    if (params.fibLib) {
      if (params.verbosity >= LogLevel::ParsedFiles) {
        std::cout << FBLU(BOLD("File Log : \n")) "Parse internal lib : " FBLU(
            "Fibonacci lib") "\n";
      }
      std::stringstream str(libraries::fibLibrary);
      parseStream(parser, "Fibonacci library", str);
    }

    // parse files
    for (auto &it : params.files) {
      if (params.verbosity >= LogLevel::ParsedFiles) {
        std::cout << FBLU(BOLD("File Log : \n")) "Parse file : " FBLU(
            "" + it + "") "\n";
      }
      parseFile(parser, it);
    }

    // save program
    auto program = parser.getProgram();

    if (params.verbosity > LogLevel::NoLog) {
      std::cout << FRED(BOLD("END\n")) << FBLU(BOLD("RUN : \n"));
      ;
    }

    // run program
    try {
      program->run();
    } catch (Exception &error) {
      if (params.verbosity >= LogLevel::Errors) {
        std::cerr << error.what() << std::endl;
      } else {
        (void)error;
      }
      return -1;
    }
  }
  return 0;
}
