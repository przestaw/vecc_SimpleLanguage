file(GLOB SCANNER_INC "${PROJECT_SOURCE_DIR}/include/scanner/*.h")
file(GLOB PARSER_INC "${PROJECT_SOURCE_DIR}/include/parser/*.h")
file(GLOB ERROR_INC "${PROJECT_SOURCE_DIR}/include/error/*.h")
file(GLOB INC "${PROJECT_SOURCE_DIR}/include/*.h")

add_subdirectory("AST")

include_directories("AST" "error" "scanner" "parser")

set(LIB_INC ${LIB_INC} ${PARSER_INC} ${SCANNER_INC} ${ERROR_INC} ${INC} PARENT_SCOPE)