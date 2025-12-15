#include "timerGroup_example.hpp"

#include <iostream>

int main()
{
    run_func();
    print_node<myTimers, GroupAll, std::chrono::milliseconds::period>(
        std::cout);
    return 0;
}
