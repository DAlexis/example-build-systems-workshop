cmake_minimum_required(VERSION 2.8)

project(library-test)

find_package (GTest REQUIRED)

include_directories (
    ${GTEST_INCLUDE_DIR}
    ${example-lib_SOURCE_DIR}
)

set(EXE_SOURCES
    libtest.cpp
)

add_executable(${PROJECT_NAME} ${EXE_SOURCES})

target_link_libraries (${PROJECT_NAME}
    gtest
    gtest_main
    example-lib
)

add_test(NAME Library_testing
         COMMAND ${PROJECT_NAME})
