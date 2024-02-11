cmake_minimum_required(VERSION 3.27)
project(blif2verilog)

set(CMAKE_CXX_STANDARD 20)

include_directories(.)

add_library( blif2verilog_internals
        tokenizer.cpp
        tokenizer.hpp
        parser.cpp
        parser.hpp)

add_executable(blif2verilog main.cpp)

target_link_libraries(blif2verilog blif2verilog_internals)