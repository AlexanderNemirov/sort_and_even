cmake_minimum_required(VERSION 3.21.3)
project(sort_and_even)

set(CMAKE_CXX_FLAGS "-O3")

add_executable(${PROJECT_NAME} 
    src/main.cpp)
