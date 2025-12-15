#include "group_example.hpp"

#include <iostream>

int main()
{
    run_func();
    Timer::print_node<myTimers, GroupAll, std::chrono::milliseconds::period>(
        std::cout);
    return 0;
}
