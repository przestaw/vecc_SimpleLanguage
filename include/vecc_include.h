//
// Created by przemek on 27.03.2020.
//

#ifndef VECC_VECC_INCLUDE_H
#define VECC_VECC_INCLUDE_H

#include <cstdint>

namespace vecc {
    /**
     * Log Level type
     */
    enum class LogLevel : uint8_t {
        NoLog = 0,                       //!< no information outputed to stderr
        Errors,                          //!< runtime and compile errors
        ParsedFiles,                     //!< Errors & information about parsed files
        CreatedFunctions,                //!< ParsedFiles & any created function
        ExecutedStatementsAndExpressions,//!< CreatedFunctions & Executed stmt/expr
        CreatedStatementsAndExpressions, //!< ExecutedStatementsAndExpressions & Creation of stmt/expr
        ParsedTokens,                    //!< CreatedStatementsAndExpressions & any Token
        FullLog,                         //!< All available logs
    };
}

#endif //VECC_VECC_INCLUDE_H
