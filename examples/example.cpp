#include "Timer.hpp"

#include <iostream>
#include <thread>

using TimerManager = TimerRegistry<struct Timer_Measure, struct Timer_direct,
    struct Timer_Deter>;

void f()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    return;
}

void g()
{
    std::this_thread::sleep_for(std::chrono::seconds(1));
    return;
}

int main()
{
    auto &timer_measure = TimerManager::get<Timer_Measure>();
    timer_measure.measure(f);
    std::cout << timer_measure.elapsedTime<std::chrono::milliseconds::period>()
              << "ms\n";

    TimerManager::get<Timer_direct>().start();
    f();
    TimerManager::get<Timer_direct>().stop();
    std::cout << "first: " << TimerManager::get<Timer_direct>() << "s\n";

    TimerManager::get<Timer_direct>().reset();
    TimerManager::get<Timer_direct>().start();
    f();
    TimerManager::get<Timer_direct>().stop();
    std::cout << "second: " << TimerManager::get<Timer_direct>() << "s\n";

    {
        auto deterTimer = DeterTimer(TimerManager::get<Timer_Deter>());
        g();
    }
    std::cout << TimerManager::get<Timer_Deter>() << "s\n";
    std::cout << std::endl;
    return 0;
}
