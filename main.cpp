#include <iostream>
#include "scanner/reader.h"
#include "general_defines.h"

int main() {
    vecc::Reader reader(&std::cin);
    (void)reader;
    std::cout << "Hello, World!\n"
              << "from vecc lang project\n"
              << "for " BOLD("TKOM ") DIM("[Compilation Techniques]") " classes\n"
              << FBLU(INV("by Stawczyk Przemyslaw") "\n");

    std::cout << reader.getCurrentPos() << '\n';
    return 0;
}
