cmake_minimum_required(VERSION 3.15)
project(code)

set(CXX_FLAGS -std=c++11 -Ofast)

add_executable(code main.cpp data.hpp string.cpp user.hpp vector.h Bpt_and_database.cpp HashMap.h)