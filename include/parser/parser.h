//
// Created by przemek on 19.03.2020.
//

#ifndef VECC_LANG_PARSER_H
#define VECC_LANG_PARSER_H

#include <scanner/reader.h>
#include <scanner/scanner.h>
#include <AST/general/program.h>

namespace vecc {
    class Parser{
    public:
        Parser();
        //Parser(Scanner scan); // FIXME : is it needed? will i change scanner for any reason
        //void setlexer(Scanner scan);
        void setSource(std::unique_ptr<Reader> source);

        Program parse();    // FIXME : run multiple times as source changes?
        // FIXME : may be replaced with :
        //void parse();
        //Program getProgram();

        void cleanParser(); // to clean AST tree / new program

    private:
        Scanner internalScanner; // NOTE : or std::unique_ptr<Scanner>
    };
}

#endif //VECC_LANG_PARSER_H
