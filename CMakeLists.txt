cmake_minimum_required(VERSION 3.27)

project(Timer)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(Timer STATIC ${PROJECT_SOURCE_DIR}/src/Timer.cpp)
target_include_directories(Timer PUBLIC ${PROJECT_SOURCE_DIR}/timer)

# add_executable(timerExample ${PROJECT_SOURCE_DIR}/examples/example.cpp)
# target_link_libraries(timerExample Timer)

# add_executable(timerGroupExample ${PROJECT_SOURCE_DIR}/examples/timerGroup_example_main.cpp ${PROJECT_SOURCE_DIR}/examples/timerGroup_example_func.cpp)
# target_link_libraries(timerGroupExample Timer)

add_subdirectory(examples)