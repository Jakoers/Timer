#include "Timer.hpp"

#include <iostream>
#include <thread>

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
    Timer timer;
    timer.measure(f);
    std::cout << timer.elapsedTime<std::chrono::milliseconds::period>()
              << "ms\n";

    timer.reset();
    timer.start();
    f();
    f();
    timer.stop();
    std::cout << timer << "s\n";

    timer.reset();
    {
        auto deterTimer = DeterTimer(timer);
        g();
    }
    std::cout << timer << "s\n";
    std::cout << std::endl;
    return 0;
}
