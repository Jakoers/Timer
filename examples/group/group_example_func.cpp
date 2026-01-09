#include "group_example.hpp"

#include <thread>

void f(int sleepTimeMs = 100)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(sleepTimeMs));
    return;
}

void run_func()
{
    myTimers::get<Timer11>().measure(f, 100);
    myTimers::get<Timer12>().measure(f, 100);
    myTimers::get<Timer2>().start();
    myTimers::get<Timer21>().measure(f, 500);
    myTimers::get<Timer22>().measure(f, 500);
    f(100);
    myTimers::get<Timer2>().stop();
}
