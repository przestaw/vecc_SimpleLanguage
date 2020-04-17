file(GLOB AST_TEST "${PROJECT_SOURCE_DIR}/test/AST/general/*.cpp")
file(GLOB AST_STATEMENT_TEST "${PROJECT_SOURCE_DIR}/test/AST/statement/*.cpp")
file(GLOB AST_EXPRESSION_TEST "${PROJECT_SOURCE_DIR}/test/AST/expression/*.cpp")

include_directories("expression" "general" "statement")

set(TEST_SRC ${TEST_SRC} ${AST_TEST} ${AST_STATEMENT_TEST} ${AST_EXPRESSION_TEST} PARENT_SCOPE)