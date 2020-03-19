file(GLOB SCANNER_SRC "${PROJECT_SOURCE_DIR}/src/scanner/*.cpp")
file(GLOB PARSER_SRC "${PROJECT_SOURCE_DIR}/src/parser/*.cpp")

add_subdirectory("AST")

set(LIB_SRC ${LIB_SRC} ${SCANNER_SRC} ${PARSER_SRC} PARENT_SCOPE)
