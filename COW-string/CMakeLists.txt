cmake_minimum_required(VERSION 3.14)

project(greatstr)

option(BUILD_TESTS "Build tests" ON)

add_compile_options(-std=c++20 -Wall)

set(SOURCE_EXE main/main.cpp
   )

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(useStr ${SOURCE_EXE})

add_subdirectory(lib/greatstr)

if (BUILD_TESTS)
  add_subdirectory(Test)
endif (BUILD_TESTS)

target_link_libraries(useStr greatstr)
