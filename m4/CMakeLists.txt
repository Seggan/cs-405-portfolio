cmake_minimum_required(VERSION 4.1)
project(m4)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)

FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(m4_tests main2.cpp)
target_link_libraries(m4_tests PRIVATE GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(m4_tests)
