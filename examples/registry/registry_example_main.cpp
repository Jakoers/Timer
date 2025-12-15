#include "registry_example.hpp"

#include <iostream>

int main()
{
    run_func();
    std::cout << myTimers::get<TimerF1>() << "s\n";
    std::cout << myTimers::get<TimerF2>() << "s\n";
    std::cout << myTimers::get<TimerF3>() << "s\n";

    std::cout << std::endl;
    return 0;
}
