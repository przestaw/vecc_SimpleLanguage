set(CMAKE_INTERPROCEDURAL_OPTIMIZATION FALSE)

file(GLOB TEST_SRC "${PROJECT_SOURCE_DIR}/test/*.cpp")
file(GLOB TEST_SCANNER "${PROJECT_SOURCE_DIR}/test/scanner/*.cpp")
file(GLOB TEST_PARSER "${PROJECT_SOURCE_DIR}/test/parser/*.cpp")
file(GLOB TEST_INC "${PROJECT_SOURCE_DIR}/test/AST/*.h")
set(TEST_SRC ${TEST_SRC} ${TEST_SCANNER} ${TEST_PARSER})

include_directories(AST)
add_subdirectory(AST)
add_executable(${TEST} ${TEST_SRC} ${TEST_INC} ${LIB_SRC} ${LIB_INC})
target_link_libraries(${TEST} ${EXTERNAL_LIBS} ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})

add_test(runTest "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${TEST}")

if (CMAKE_CONFIGURATION_TYPES)
    add_custom_target(${CHECK} COMMAND ${CMAKE_CTEST_COMMAND}
            --force-new-ctest-process --output-on-failure
            --build-config "$<CONFIGURATION>"
            DEPENDS ${TEST})
else ()
    add_custom_target(${CHECK} COMMAND ${CMAKE_CTEST_COMMAND}
            --force-new-ctest-process --output-on-failure
            DEPENDS ${TEST})
endif ()