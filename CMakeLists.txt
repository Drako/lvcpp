cmake_minimum_required(VERSION 3.13)
cmake_policy(VERSION 3.13)
project(lvcpp VERSION 0.1.0.0)

set(CMAKE_CXX_STANDARD 17)

add_library(lvcpp INTERFACE)
target_sources(lvcpp INTERFACE include/lv/utilities.hxx include/lv/sequence.hxx)
target_include_directories(lvcpp INTERFACE include/)

enable_testing()
add_executable(lvcpp_tests test/catch.hpp test/main.cxx test/utilities.cxx test/sequence.cxx)
target_link_libraries(lvcpp_tests lvcpp)

add_test(NAME tests COMMAND lvcpp_tests)
