cmake_minimum_required(VERSION 3.27)

project(Timer)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(Timer STATIC ${PROJECT_SOURCE_DIR}/src/timer.cpp)
target_include_directories(Timer PUBLIC ${PROJECT_SOURCE_DIR}/include)

if(NOT EXISTS ${CMAKE_CURRENT_LIST_DIR}/.disable_example_tests)
    add_subdirectory(examples)
endif()