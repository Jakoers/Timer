cmake_minimum_required(VERSION 3.27)

add_executable(basic basic/basic_example.cpp)
target_link_libraries(basic Timer)

add_executable(registry registry/registry_example_main.cpp registry/registry_example_func.cpp)
target_link_libraries(registry Timer)

add_executable(group group/group_example_main.cpp group/group_example_func.cpp)
target_link_libraries(group Timer)