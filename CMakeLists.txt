cmake_minimum_required(VERSION 3.15)
project(code)

set(CXX_FLAGS -std=c++11 -O3 -Og -pg)

add_executable(code main.cpp data.hpp string.cpp user.hpp HashMap.h cache.h Bpt_and_database.cpp)