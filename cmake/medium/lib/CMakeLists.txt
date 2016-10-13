cmake_minimum_required(VERSION 3.1)

project(example-lib)

set(LIB_SOURCE
    libsource.cpp
)

add_library(${PROJECT_NAME} STATIC ${LIB_SOURCE})

target_compile_features(${PROJECT_NAME} PUBLIC cxx_rvalue_references)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_lambdas)
