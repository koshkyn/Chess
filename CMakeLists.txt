cmake_minimum_required(VERSION 3.15)
project(chess)

set(CMAKE_CXX_STANDARD 17)

add_executable(chess main.cpp square.h square.cpp Figure.h Figure.cpp Field.h Field.cpp)