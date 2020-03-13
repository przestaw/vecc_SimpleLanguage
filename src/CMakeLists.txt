cmake_policy(SET CMP0069 NEW)
include(CheckIPOSupported)
check_ipo_supported()

set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)

file(GLOB SCANNER_SRC "${PROJECT_SOURCE_DIR}/src/scanner/*.cpp")

set(LIB_SRC ${LIB_SRC} ${SCANNER_SRC})

add_library(${LIBRARY} ${LIB_SRC} ${LIB_INC})

add_dependencies(${LIBRARY} ${CHECK})