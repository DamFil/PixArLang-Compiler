cmake_minimum_required(VERSION 3.25)
project(Assignment)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Assignment
        Scanner/FileStreamHandler.h
        Scanner/Scanner.cpp
        Scanner/Scanner.h
        Tests/test.cpp
        Scanner/TokenStruct.h)
