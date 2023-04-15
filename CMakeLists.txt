cmake_minimum_required(VERSION 3.25)
project(Assignment)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Assignment
        FileStreamHandler.h
        Scanner.cpp
        Scanner.h
        test.cpp
        TokenStruct.h)
