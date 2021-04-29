cmake_minimum_required(VERSION 3.13)
cmake_policy(VERSION 3.13)
project(lvcpp VERSION 0.1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CATCH_BUILD_STATIC_LIBRARY ON)

enable_testing()

include(FetchContent)
FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v2.13.6
)
FetchContent_GetProperties(Catch2)
if (NOT Catch2_POPULATED)
    FetchContent_Populate(Catch2)
    add_subdirectory(${catch2_SOURCE_DIR} ${catch2_BINARY_DIR})
endif ()

add_library(lvcpp INTERFACE)
target_sources(lvcpp INTERFACE
        include/lv/cpp.hxx
        include/lv/utilities.hxx include/lv/sequence.hxx
        include/lv/collector.hxx
        include/lv/mapper.hxx)
target_include_directories(lvcpp INTERFACE include/)

add_executable(lvcpp_tests
        test/utilities.cxx test/sequence.cxx test/collector.cxx
        test/mapper.cxx)
target_link_libraries(lvcpp_tests PRIVATE lvcpp Catch2::Catch2WithMain)

add_test(NAME tests COMMAND lvcpp_tests)

install(DIRECTORY include/lv DESTINATION include)
