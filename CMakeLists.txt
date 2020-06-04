cmake_minimum_required(VERSION 3.10)
set(PROJECT_NAME vecc)
project(${PROJECT_NAME})

set(PROJECT_DESCRIPTION "Vector Capable Simple Language")

set(CMAKE_CXX_STANDARD 17)

set(EXECUTABLE ${PROJECT_NAME}-program)
set(LIBRARY ${PROJECT_NAME}-lib)
set(TEST ${PROJECT_NAME}-test)
set(CHECK ${TEST}-check)
set(DOC ${PROJECT_NAME}-doc)

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake_modules/finders")
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake_modules")

include(CTest)
enable_testing()

find_package(LATEX)
find_package(Doxygen)
find_package(Boost COMPONENTS program_options unit_test_framework REQUIRED)
set(EXTERNAL_LIBS "Boost::program_options")

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    # using Clang
    set(CMAKE_CXX_FLAGS_DEBUG   "${CMAKE_CXX_FLAGS_DEBUG}   -O0 -g -Werror -Wextra-tokens -Wambiguous-member-template -Wshadow -Wall -pedantic -Wextra -Wold-style-cast")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -finline-functions -fmerge-all-constants -fvectorize -flto")

    include(LLVMtoolchain)

    set(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} -fuse-ld=gold)

    set(CMAKE_C_ARCHIVE_CREATE "<CMAKE_AR> qcs <TARGET> <LINK_FLAGS> <OBJECTS>")
    set(CMAKE_C_ARCHIVE_FINISH   true)
    set(CMAKE_CXX_ARCHIVE_CREATE "<CMAKE_AR> qcs <TARGET> <LINK_FLAGS> <OBJECTS>")
    set(CMAKE_CXX_ARCHIVE_FINISH true)

elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    if(CMAKE_BUILD_TYPE EQUAL Release)
        cmake_policy(SET CMP0069 NEW)
        include(CheckIPOSupported)
        check_ipo_supported()

        set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
    endif()

    # using GCC
    set(CMAKE_CXX_FLAGS_DEBUG   "${CMAKE_CXX_FLAGS_DEBUG}   -O0 -Og -g -Werror -Wshadow -Wall -pedantic -Wextra -Wold-style-cast")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -finline-functions -fdevirtualize -fmerge-constants")

    include(GNUtoolchain)
endif()

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE})

include_directories("${PROJECT_SOURCE_DIR}/include" ${BOOST_INCLUDE_DIR})

#Include src and test for library and test-check
add_subdirectory("include")
add_subdirectory("src")
add_subdirectory("test")

#library
add_library(${LIBRARY} ${LIB_SRC} ${LIB_INC})
add_dependencies(${LIBRARY} ${CHECK})

#Program executable
add_executable(${EXECUTABLE} src/main.cpp)
add_dependencies(${EXECUTABLE} ${LIBRARY})
target_link_libraries(${EXECUTABLE} ${LIBRARY})
target_link_libraries(${EXECUTABLE} ${EXTERNAL_LIBS})

# "all" target
if(LATEX_FOUND OR DOXYGEN_FOUND)
    add_subdirectory(doc)
    add_custom_target(build-all DEPENDS ${DOC} ${PROGRAM} ${LIB} ${CHECK} ${TEST})
else()
    add_custom_target(build-all DEPENDS ${PROGRAM} ${LIB} ${CHECK} ${TEST})
endif()
