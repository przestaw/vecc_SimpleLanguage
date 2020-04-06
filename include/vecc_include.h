//
// Created by przemek on 27.03.2020.
//

#ifndef VECC_VECC_INCLUDE_H
#define VECC_VECC_INCLUDE_H

#include <cstdint>
#include <string>

namespace vecc {
    /**
     * Log Level type
     */
    enum class LogLevel : uint8_t {
        NoLog = 0,                       //!< no information outputed to stderr
        Errors,                          //!< runtime and compile errors
        ParsedFiles,                     //!< Errors & information about parsed files
        CreatedFunctions,                //!< ParsedFiles & any created function
        ParsedTokens,                    //!< ParsedFiles & any Token
        FullLog,                         //!< All available logs
    };

    namespace libraries {
        /**
         * Vecc Library source constant
         */
        static const std::string &veccLibrary = "fun product2(vec1, vec2) {\n"
                                                "    var res=vec(0,0);\n"
                                                "    res[0] = vec1[0] * vec2[0] - vec1[1] * vec2[1];\n"
                                                "    res[1] = vec1[0] * vec2[1] + vec1[1] * vec2[0];\n"
                                                "    return res;"
                                                "}\n"
                                                "\n"
                                                "fun product3(vec1, vec2) {\n"
                                                "    var res=vec(0,0,0);\n"
                                                "    res[0] = vec1[1] * vec2[2] - vec1[2] * vec2[1];\n"
                                                "    res[1] = vec1[2] * vec2[0] - vec1[0] * vec2[2];\n"
                                                "    res[2] = vec1[0] * vec2[1] - vec1[1] * vec2[0];\n"
                                                "    return res;\n"
                                                "}\n"
                                                "\n"
                                                "fun scalar2(vec1, vec2) {\n"
                                                "    var res = vec1[0] * vec2[0] + vec1[1] * vec2[1];\n"
                                                "    return res;\n"
                                                "}\n"
                                                "\n"
                                                "fun scalar3(vec1, vec2) {\n"
                                                "    var res = vec1[0] * vec2[0] + vec1[1] * vec2[1] + vec1[2] * vec2[2];\n"
                                                "    return res;\n"
                                                "}\n";

        /**
         * Fib Library source constant
         */
        static const std::string &fibLibrary = "fun fib_rec(n){\n"
                                               "    if(n <= 1){\n"
                                               "        return 1;\n"
                                               "    } else {\n"
                                               "        return fib_rec(n-1) + fib_rec(n-2);\n"
                                               "    }\n"
                                               "}\n"
                                               "\n"
                                               "fun fib_it(n){\n"
                                               "    var a = 0;\n"
                                               "    if( n == 0){\n"
                                               "        return a;\n"
                                               "    }\n"
                                               "    var b = 1;\n"
                                               "    var c = a + b;\n"
                                               "\n"
                                               "    while(0 < n){\n"
                                               "        c = a + b;\n"
                                               "        a = b;\n"
                                               "        b = c;\n"
                                               "        \n"
                                               "        n = n - 1;\n"
                                               "    }\n"
                                               "    return b;\n"
                                               "}\n";
    }
}


#endif //VECC_VECC_INCLUDE_H
