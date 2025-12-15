#pragma once
#ifndef TIMER_REGISTRY_C74F283F_6911_4EF0_B29B_4FFB31E9C808
#    define TIMER_REGISTRY_C74F283F_6911_4EF0_B29B_4FFB31E9C808

#    include "timer_core.hpp"

namespace Timer
{
template <typename... Tags>
class TimerRegistry
{
public:
    template <typename Tag>
    static Timer &get()
    {
        static Timer t;
        return t;
    }

private:
    template <typename Tag>
    inline static Timer timers;
};
} // namespace Timer

#endif /* TIMER_REGISTRY_C74F283F_6911_4EF0_B29B_4FFB31E9C808 */
