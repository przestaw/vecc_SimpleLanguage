//
// Created by przemek on 13.03.2020.
//

#ifndef VECC_LANG_SCANNER_H
#define VECC_LANG_SCANNER_H

#include <memory>
#include "scanner/token.h"
#include "scanner/reader.h"

namespace vecc {

    class Scanner {
    public:
        Scanner();

        Scanner(std::unique_ptr<Reader> reader);

        Token getToken();
        Token parseToken();

        // I assume that diffrent readers will be used only to load error-free libraries
        // Hence that errors that occur will be conected only with single input file

        // TODO : consider information about source (file/stream)
        //  in Exceptions (reader or position with origin info - file/lib)
        void setReader(std::unique_ptr<Reader> reader);
    private:
        Token currentToken;
        // use built-in std::unique_ptr check if ptr is "valid" (!= nullptr)
        inline bool canRead() { return static_cast<bool>(reader_); }

        inline void tryToken();

        inline void tryKeyword();
        inline void tryCharString();
        inline void tryNumberString();
        inline void tryOperatorOrBracket();

        std::unique_ptr<Reader> reader_;
    };
}
#endif //VECC_LANG_SCANNER_H