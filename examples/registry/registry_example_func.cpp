#include "registry_example.hpp"

#include <thread>

void f(int sleepTimeMs = 100)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(sleepTimeMs));
    return;
}

void run_func()
{
    myTimers::get<TimerF1>().measure(f, 100);
    myTimers::get<TimerF2>().measure(f, 200);
    Timer::measure(myTimers::get<TimerF3>(), f, 300);
}
