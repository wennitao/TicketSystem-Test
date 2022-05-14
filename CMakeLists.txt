cmake_minimum_required(VERSION 3.15)
project(rollback)

set(CXX_FLAGS -std=c++17 -Ofast)

# add_executable(code data.hpp string.cpp user.hpp HashMap.h cache.h Bptest.cpp Bpt_and_database.cpp Bpt_and_database.h)
add_executable(rollback main.cpp data.hpp string.cpp user.hpp HashMap.h cache.h B+Tree.hpp log.hpp)