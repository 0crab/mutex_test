cmake_minimum_required(VERSION 3.17)
project(mutex_test)

set(CMAKE_CXX_STANDARD 11)

SET(CMAKE_BUILD_TYPE "Release")

link_libraries(pthread)

add_executable(mutex_test main.cpp)