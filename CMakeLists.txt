cmake_minimum_required(VERSION 3.15)
project(vecc)

set(CMAKE_CXX_STANDARD 17)

set(EXECUTABLE ${PROJECT_NAME}-program)
set(LIBRARY ${PROJECT_NAME}-lib)
set(TEST ${PROJECT_NAME}-test)
set(CHECK ${TEST}-check)
set(DOC ${PROJECT_NAME}-doc)

file(GLOB LIB_SRC "src/*.cpp")
file(GLOB LIB_INC "include/*.h")
file(GLOB TEST_SRC "test/*.cpp")

include(CTest)
enable_testing()

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Og -g3 -Wshadow -Wall -pedantic -Wextra -Wold-style-cast")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -finline-functions")

if(CMAKE_BUILD_TYPE EQUAL Release)
    cmake_policy(SET CMP0069 NEW)
    include(CheckIPOSupported)
    check_ipo_supported()

    set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE})

find_package(Boost COMPONENTS program_options unit_test_framework REQUIRED)
set(EXTERNAL_LIBS "Boost::program_options")
include_directories("${PROJECT_SOURCE_DIR}/include" ${BOOST_INCLUDE_DIR})

#Include src and test for library and test-check
find_package(LATEX)
if(LATEX_FOUND)
    add_subdirectory(doc)
endif()
add_subdirectory("include")
add_subdirectory("src")
add_subdirectory("test")

#library
add_library(${LIBRARY} ${LIB_SRC} ${LIB_INC})
add_dependencies(${LIBRARY} ${CHECK})

#Program executable
add_executable(${EXECUTABLE} main.cpp)
add_dependencies(${EXECUTABLE} ${LIBRARY})
target_link_libraries(${EXECUTABLE} ${LIBRARY} ${EXTERNAL_LIBS})

# "all" target
if(LATEX_FOUND)
    add_custom_target(build-all DEPENDS ${DOC} ${PROGRAM} ${LIB} ${CHECK} ${TEST})
else()
    add_custom_target(build-all DEPENDS ${PROGRAM} ${LIB} ${CHECK} ${TEST})
endif()
