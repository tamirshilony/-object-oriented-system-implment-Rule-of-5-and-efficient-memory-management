cmake_minimum_required(VERSION 3.17)
project(Ass1)

set(CMAKE_CXX_STANDARD 11)

add_executable(ass_1
        include/Agent.h
        include/Graph.h
        include/json.hpp
        include/Session.h
        include/Tree.h
        src/main.cpp)