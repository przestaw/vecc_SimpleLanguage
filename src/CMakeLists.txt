cmake_policy(SET CMP0069 NEW)
include(CheckIPOSupported)
check_ipo_supported()

set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)

add_library(${LIBRARY} ${LIB_SRC} ${LIB_INC})

add_dependencies(${LIBRARY} ${CHECK})