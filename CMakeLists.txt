cmake_minimum_required(VERSION 3.6)
project(course_2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")

set(SOURCE_FILES list.cpp listTest.cpp main.cpp tour.cpp logic.cpp)
add_executable(course_2 ${SOURCE_FILES})