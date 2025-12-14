cmake_minimum_required(VERSION 3.27)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(Timer)

add_library(Timer INTERFACE Timer.hpp)
target_include_directories(Timer INTERFACE ${PROJECT_SOURCE_DIR})

add_executable(timerExample ${PROJECT_SOURCE_DIR}/examples/example.cpp)
target_link_libraries(timerExample Timer)