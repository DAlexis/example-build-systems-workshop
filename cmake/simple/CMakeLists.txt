cmake_minimum_required(VERSION 3.1)
set(CMAKE_CXX_STANDARD 11)
project(hello_world)

find_package(Threads)

include_directories(include)

add_executable(hello_world
    include/file1.hpp
    include/file2.hpp
    src/file1.cpp
    src/file2.cpp
    src/main.cpp
)

target_link_libraries(hello_world ${CMAKE_THREAD_LIBS_INIT})
