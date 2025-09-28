cmake_minimum_required(VERSION 3.14)

project(greatstr)
enable_testing()

option(BUILD_TESTS "Build tests" ON)

add_compile_options(-std=c++20 -Wall)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_subdirectory(lib/greatstr)

if (BUILD_TESTS)
  add_subdirectory(Test)
endif (BUILD_TESTS)

find_package(benchmark REQUIRED)
add_executable(benchGreatStr main/main.cpp)
target_link_libraries(benchGreatStr benchmark::benchmark)

