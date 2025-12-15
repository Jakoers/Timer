#pragma once
#ifndef REGISTRY_EXAMPLE_C4C4838E_294B_4CC3_87D4_5C75AD1E03C5
#    define REGISTRY_EXAMPLE_C4C4838E_294B_4CC3_87D4_5C75AD1E03C5

#    include "timer/timer.hpp"

// 在头文件中注册若干个Timer
using myTimers =
    Timer::TimerRegistry<struct TimerF1, struct TimerF2, struct TimerF3>;

void run_func();

#endif /* REGISTRY_EXAMPLE_C4C4838E_294B_4CC3_87D4_5C75AD1E03C5 */
