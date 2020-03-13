//
// Created by przemek on 13.03.2020.
//

#ifndef PROJECT_READER_H
#define PROJECT_READER_H

#include <iostream>

namespace vecc {

    class Reader {
    public:
        Reader();
        Reader(std::istream *input);
    private:
        /**
         * Pointer to allow changing stream during execution
         */
        std::istream *stream_;
    };

}

#endif //PROJECT_READER_H
