//
// Created by przemek on 27.03.2020.
//

#ifndef VECC_VECC_INCLUDE_H
#define VECC_VECC_INCLUDE_H

#include <cstdint>

namespace vecc{
    enum class LogLevel : uint8_t{
        NoLog = 0,
        Errors,
        ParsedFiles,
        CreatedFunctionsVariables,
        ExecutedStatementsAndExpressions,
        CreatedStatementsAndExpressions,
        ParsedTokens,
        ReadCharacters,
        PeakedCharacters,
        FullLog,
    };
}

#endif //VECC_VECC_INCLUDE_H
