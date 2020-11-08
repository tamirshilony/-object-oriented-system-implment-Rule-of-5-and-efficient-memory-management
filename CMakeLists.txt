cmake_minimum_required(VERSION 3.17)
project(spl_1)

set(CMAKE_CXX_STANDARD 11)

<<<<<<< HEAD
add_executable(spl_1  include/Agent.h
=======
add_executable(Ass1
        include/Agent.h
>>>>>>> 48beafb10363a212786d3b75cafd356855a4edb6
        include/Graph.h
        include/json.hpp
        include/Session.h
        include/Tree.h
        src/main.cpp
        src/Session.cpp
        src/Agent.cpp
        src/Tree.cpp
        src/Graph.cpp)