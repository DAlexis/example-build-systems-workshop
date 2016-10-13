cmake_minimum_required(VERSION 3.1)

project("Project-name")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -g -DDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -g -DNDEBUG")

add_subdirectory(lib)
add_subdirectory(program)

# To enable ctest usage
enable_testing()

add_subdirectory(unit-tests)
