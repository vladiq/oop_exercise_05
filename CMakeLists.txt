cmake_minimum_required(VERSION 3.1)

project(lab5)

add_executable(lab5
    main.cpp)

set_property(TARGET lab5 PROPERTY CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Wextra -Werror")
