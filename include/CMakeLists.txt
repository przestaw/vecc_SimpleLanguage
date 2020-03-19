file(GLOB SCANNER_INC "${PROJECT_SOURCE_DIR}/include/scanner/*.h")
file(GLOB PARSER_INC "${PROJECT_SOURCE_DIR}/include/parser/*.h")
file(GLOB ERROR_INC "${PROJECT_SOURCE_DIR}/include/error/*.h")

add_subdirectory("AST")

set(LIB_INC ${LIB_INC} ${SCANNER_INC} ${PARSER_INC} ${ERROR_INC} PARENT_SCOPE)