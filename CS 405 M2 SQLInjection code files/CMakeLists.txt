cmake_minimum_required(VERSION 4.1)
project(CS_405_M2_SQLInjection_code_files)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(CS_405_M2_SQLInjection_code_files
        SQLInjection.cpp
        sqlite3.c
        sqlite3.h)
