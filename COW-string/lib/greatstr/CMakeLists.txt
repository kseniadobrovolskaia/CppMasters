cmake_minimum_required(VERSION 3.14)

project(greatstr)

add_compile_options(-std=c++20 -fPIC)

include_directories(${CMAKE_SOURCE_DIR}/include)

set(SOURCE_LIB GreatStr.cpp
 )

add_library(greatstr STATIC ${SOURCE_LIB})

