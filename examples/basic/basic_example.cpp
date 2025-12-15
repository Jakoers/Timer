#include "timer.hpp"

#include <iostream>
#include <thread>

void f(int sleepTimeMs = 100)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(sleepTimeMs));
    return;
}

int main()
{
    Timer::Timer t;

    // 手动计时
    t.start();
    f();
    t.stop();
    std::cout << "t: " << t << "s, should be around 0.1s\n";

    t.reset();
    t.start();
    f();
    // 检查当前的运行时间，方便控制总体运行时间
    while (t.peek<std::chrono::milliseconds::period>() < 600) f();
    t.stop();
    std::cout << "t: " << t.elapsedTime<std::chrono::milliseconds::period>()
              << "ms, should be around 600ms\n";

    t.reset();
    // 自动计时
    t.measure(f, 200);
    std::cout << "t: " << t << "s, should be around 0.2s\n";
    // 也可以手动停止计时
    {
        auto st = Timer::ScopedTimer(t);
        f(300);
        st.stop();
        f(300);
    }
    std::cout << "t: " << t << "s, shound be around 0.5s\n";

    std::cout << std::endl;
    return 0;
}
