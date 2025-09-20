cmake_minimum_required(VERSION 3.14)
project(tests)


# GoogleTest requires at least C++14, but for greatstr we need C++20
set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)


add_compile_options(-std=c++20)

enable_testing()

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(greatstrTests
               Test.cpp
              )

target_link_libraries(greatstrTests
                      greatstr
                      GTest::gtest_main
                     )

include(GoogleTest)
gtest_discover_tests(greatstrTests)

