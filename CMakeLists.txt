cmake_minimum_required(VERSION 3.31)
project(cpp_unique_ptr)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)

add_executable(cpp_unique_ptr
        include/unique_ptr.h
        src/main.cpp
#        tests/unique_ptr_tests.cpp # Open for test
)
