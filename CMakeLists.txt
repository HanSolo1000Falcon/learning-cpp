cmake_minimum_required(VERSION 4.1)
project(learning_projects)

set(CMAKE_CXX_STANDARD 20)

add_executable(learning_projects src/main.cpp
        src/rng/rng.cpp
        src/rng/rng.h
        src/json/json.cpp
        src/json/json.h)
