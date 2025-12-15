#include "timerGroup_example.hpp"

#include <thread>

void func_100ms()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

void func_500ms()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
}

void run_func()
{
    myTimers::get<Timer11>().measure(func_100ms);
    myTimers::get<Timer12>().measure(func_100ms);
    myTimers::get<Timer21>().measure(func_500ms);
    myTimers::get<Timer22>().measure(func_500ms);
}
